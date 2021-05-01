CC=gcc
INCLUDE := $(shell find include/ -name "*.c" -o -name "*.h")
OPENSSL=-I /usr/include/openssl -lssl -lcrypto


build_run: clean build_A run compare

run:
	./Filestuff

clean:
	rm -f cuts/* merge.jpg foto.jpg Filestuff meta.inf

build_A:
	$(CC) main.c $(INCLUDE) $(OPENSSL) -o Filestuff


compare:
	cat $(shell ls -1v cuts/ | sed 's@^@cuts/@') > foto.jpg
	cmp foto.jpg new.jpg
	cmp new.jpg merge.jpg