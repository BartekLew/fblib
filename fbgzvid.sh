#!/bin/bash -e

odir=$(pwd)
tdir=/tmp/fb-$RANDOM

mkdir -p $tdir
cd $tdir
gunzip -d -c "$odir/$1" | fb2ppm

ffmpeg -i %06d.ppm "$odir/vid.mp4"

cd "$odir"
rm -r $tdir
