#!/bin/bash

# We assume that your driver is called "ch341", use the
# DRIVER INFORMATION part of this script to search for
# your driver and substitute the rmmod and modprobe parts

set -euo pipefail

echo "# GET USB SERIAL PORT DRIVER INFORMATION"
cat /proc/tty/drivers
lsmod | grep usbserial
sudo dmesg | grep ttyUSB0
echo "> done."

echo "# RESETTING A BUSY USB SERIAL PORT"
echo -n "1-1:1.0" | sudo tee /sys/bus/usb/drivers/ch341/unbind
echo
sudo rmmod ch341
sudo rmmod usbserial
sudo modprobe ch341
echo "> done."

exit 0

