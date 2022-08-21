#! /bin/bash
dev_path="/dev/bus/usb/001/012"
parn_num="m328p"
fuse_set="-U lfuse:w:0xee:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m"
firmware_file="firmware.hex"
avrdude -c usbasp -P $dev_path -p $parn_num -F -v $fuse_set -U flash:w:$firmware_file