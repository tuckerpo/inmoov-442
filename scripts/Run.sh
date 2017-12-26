#!/bin/bash
cd ../../choreonoid
misc/script/install-requisites-ubuntu-14.04.sh
cmake .
make -j 4
