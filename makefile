CC=clang
CFLAGS=-std=c99

simulate=
debug=
ifdef simulate
	CFLAGS+=-DSIMULATE_ON_PC
	LDLIBS=-lSDL2

ifdef debug
	CFLAGS+=-fsanitize=address
	LDFLAGS+=-fsanitize=address
	CFLAGS+=-g -O0
else
	CFLAGS+=-O3
endif

	sdl_or_vga=sdl_wrapper.h
else
	CFLAGS+=--target=riscv32-unknown-unknown
  	CFLAGS+=-march=rv32im
  	CFLAGS+=-ffreestanding
  	CFLAGS+=-fno-builtin
  	CFLAGS+=-nostdlib
  	CFLAGS+=-mno-relax
  	CFLAGS+=-fno-PIE
  	CFLAGS+=-G=0
  	CFLAGS+=-Oz
  	CFLAGS+=-flto

	sdl_or_vga=vga.h
endif

objects=main.o map.o snake.o gui.o sdl_wrapper.o random.o display.o

main: $(objects)

main.o: display.h gui.h map.h snake.h

map.o: map.h random.h display.h gui.h color.h

snake.o: snake.h map.h random.h

gui.o: gui.h display.h $(sdl_or_vga) color.h

sdl_wrapper.o: sdl_wrapper.h display.h color.h

.PHONY: clean
clean:
	rm -rf *.o main
