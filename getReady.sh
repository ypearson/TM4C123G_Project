#!/bin/sh 
set -x
USR=usr
BIN=openocd
SRC=$BIN-code
TEXINFO=texinfo-6.0
URL=http://ftp.gnu.org/gnu/texinfo/$TEXINFO.tar.gz
TOP=$PWD

if [ ! -d $USR ]; then
  wget -qO- $URL | tar -xzf -
  cd $TEXINFO 
  ./configure --prefix=$TOP/$USR
  make && make install && cd $TOP; rm -rf $TEXINFO
fi

if [ ! -d  $SRC ]; then
  git clone git://git.code.sf.net/p/openocd/code $SRC 
  cd $SRC
  git checkout -b v9 v0.9.0
  ./bootstrap
  ./configure --enable-maintainer-mode --enable-ti-icidi --prefix=$TOP/$BIN
  export PATH=$TOP/$USR/bin:$PATH
  make && make install && cd $TOP; rm -rf $SRC $USR
fi
