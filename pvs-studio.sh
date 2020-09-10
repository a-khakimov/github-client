#!/bin/bash

make clean
pvs-studio-analyzer trace -- make
pvs-studio-analyzer analyze
plog-converter -a GA:1,2 -t tasklist PVS-Studio.log
