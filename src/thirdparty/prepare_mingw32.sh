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

cd libvmime-0.9.1
configure && make && make install && make clean && make distclean
cd ..