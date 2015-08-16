#!/bin/sh 
set -x
BIN=openocd
SRC=$BIN-code
TEXINFO=texinfo-6.0
URL=http://ftp.gnu.org/gnu/texinfo/$TEXINFO.tar.gz
TOP=$PWD

if [ ! -d usr ]; then
  wget -qO- $URL | tar -xzf -
  $TEXINFO/configure --prefix=$TOP/usr
  make -C $TEXINFO && make -C $TEXINFO install
fi

if [ ! -d  $SRC ]; then
  git clone git://git.code.sf.net/p/openocd/code $SRC 
  cd $SRC
  git checkout -b v9 v0.9.0
  ./bootstrap
  ./configure --enable-maintainer-mode --enable-ti-icidi --prefix=$TOP/$BIN
  make && make install
  cd $TOP
fi
