#!/bin/bash

set -e

BUILD_DIR="build"
RELEASE_DIR="release"

echo "== === =="

mkdir -p "$BUILD_DIR"
mkdir -p "$RELEASE_DIR"

cd "$BUILD_DIR"

# generate cmake
if [ ! -f Makefile ]; then
    echo "--= Running cmake config =--"
    cmake -DCMAKE_BUILD_TYPE=Release ..
fi


echo "--= Building project =--"
cmake --build . -j$(nproc)


cd ..

# copy binary to release
if [ -f "$BUILD_DIR/bot" ]; then
    echo "-- Moving binary to release/"
    cp "$BUILD_DIR/bot" "$RELEASE_DIR/"
    rm -rf "$BUILD_DIR"
else
    echo "!! Binary not found: $BUILD_DIR/bot"
    exit 1
fi

echo "== Build finished successfully =="
