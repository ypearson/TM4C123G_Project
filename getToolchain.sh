#!/bin/sh

if [ ! -d arm ]; then
  URL=https://launchpad.net/gcc-arm-embedded/4.8/4.8-2014-q3-update/+download/gcc-arm-none-eabi-4_8-2014q3-20140805-linux.tar.bz2
  mkdir -p arm
  wget -qO- $URL | tar -C arm/ -xjf -
fi


