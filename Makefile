CC=gcc
INCLUDE := $(shell find src/include/ -name "*.c" -o -name "*.h")
OPENSSL=-I /usr/include/openssl -lssl -lcrypto
FLAGS=-Werror -Wpedantic -Wall

build_run: clean build_A run compare

run:
	./Filestuff

clean:
	rm -f cuts/* merge.jpg foto.jpg Filestuff meta.inf

build_A:
	$(CC) src/main.c $(INCLUDE) $(OPENSSL) -o Filestuff $(FLAGS)


compare:
	cat $(shell ls -1v cuts/ | sed 's@^@cuts/@') > foto.jpg
	cmp foto.jpg new.jpg
	cmp new.jpg merge.jpg

sonar:
	build/build-wrapper-linux-x86-64 --out-dir build/ make build_run