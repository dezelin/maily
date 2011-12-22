#!/bin/bash

cd libntlm-1.3
configure && make && make install && make clean && make distclean
cd ..

cd libidn-1.23
configure && make && make install && make clean && make distclean
cd ..

cd gss-0.1.5
configure && make && make install && make clean && make distclean
cd ..

cd libgsasl-1.6.1
configure && make && make install && make clean && make distclean
cd ..

cd zlib-1.2.5
make -f win32/Makefile.gcc
cp zlib.h /usr/local/include/
cp zconf.h /usr/local/include/
cp libz.a /usr/local/lib/
cp libzdll.a /usr/local/lib/libz.dll.a
make -f win32/Makefile.gcc clean
cd ..

cd libgpg-error-1.10
configure && make
rm po/*.po
make install && make clean && make distclean
cd ..

cd libgcrypt-1.5.0
configure && make && make install & make clean && make distclean
cd ..

cd gnutls-2.12.9
configure --disable-guile --enable-threads=win32 --with-libgcrypt --without-p11-kit
touch lib/libgnutls-26.def
touch lib/libgnutls-extra-26.def
touch lib/libgnutls-openssl-26.def
make && make install && make clean && make distclean
cd ..

cd libvmime-0.9.1
export CPPFLAGS="-I/usr/local/include/"
export LDFLAGS="-L/usr/local/lib/"
export LIBGNUTLS_CFLAGS="-I/usr/local/include/"
export LIBGNUTLS_LIBS="-L/usr/local/lib/ -lgnutls -lgcrypt -L/usr/local/lib -lgpg-error -lws2_32 -R/usr/local/lib -L/usr/local/lib -lz -R/usr/local/lib"
configure --enable-debug --enable-shared
make && make install && make clean
cd ..