cat $(ls -1v cmake-build-debug/here | sed 's@^@cmake-build-debug/here/@') > foto.jpg
cmp cmake-build-debug/new.jpg foto.jpg
cmp cmake-build-debug/merge.jpg cmake-build-debug/new.jpg
rm foto.jpg cmake-build-debug/merge.jpg