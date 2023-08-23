#/usr/bin/bash

cmake -S. -Bbuild
cd build
make
./TlmParserTests
