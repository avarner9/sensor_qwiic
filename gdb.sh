#!/bin/bash

set -u
set -m

openocd -f ./openocd.cfg -c init &
 
gdb-multiarch -s sensor_qwiic.elf --ex 'target remote 127.0.0.1:3333'

kill %+

