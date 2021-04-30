cat $(ls -1v cmake-build-debug/here | sed 's@^@cmake-build-debug/here/@') > foto.jpg
cmp cmake-build-debug/new.jpg foto.jpg
rm foto.jpg