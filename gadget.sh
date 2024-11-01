#!/bin/bash
set -ex
cd /sys/kernel/config/usb_gadget/
mkdir gadget
cd gadget
echo 0x18d1 > idVendor
echo 0xd00d > idProduct
echo 0x0302 > bcdUSB
mkdir configs/a.1
mkdir strings/0x409
echo 1234567890 > strings/0x409/serialnumber
echo Linux > strings/0x409/manufacturer
echo Fastboot > strings/0x409/product
echo 1 > os_desc/use
echo 0x1 > os_desc/b_vendor_code
echo MSFT100 > os_desc/qw_sign
ln -s configs/a.1 os_desc/a.1
mkdir configs/a.1/strings/0x409
echo fastboot > configs/a.1/strings/0x409/configuration
mkdir functions/ffs.fastboot
ln -s functions/ffs.fastboot configs/a.1/f1
mkdir -p /dev/usb-ffs/fastboot
mount -t functionfs fastboot /dev/usb-ffs/fastboot
ufastbootd -d /dev/usb-ffs/fastboot &
sleep 1
for i in /sys/class/udc/*
do      [ -h "${i}" ]||continue
        basename "$i" > UDC
        break
done