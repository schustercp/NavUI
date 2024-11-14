# Navigation Helper UI for a NMEA 2000 network.
This software is desighned to run on a Raspberry Pi Zero 2W connected to a HyperPixel 4inch X 4inch display.

https://shop.pimoroni.com/products/hyperpixel-4-square?variant=30138251444307
https://www.adafruit.com/product/4499

Mine is not the touch screen but Adafruit is not selling that any more.

This device will interface with the N2K network by subscribing to a brodcaast UDP socket.

## Things to install on a light Raspberry Pi image
```
  sudo apt-get install xserver-xorg
  sudo apt-get install xinit
  sudo apt-get install x11-xserver-utils
  sudo apt-get install blackbox
  sudo apt-get install xterm
  sudo apt-get install lightdm
  sudo apt-get install gtk+-3.0
```

## Copy your SSH key over so you will be able to SSH in with out a password.
```
  ssh-copy-id -i ~/.ssh/mykey user@host
```

## To add the HyperPixel Display add one of the following to the config.txt in /boot/firmware
```
Rectangular: dtoverlay=vc4-kms-dpi-hyperpixel4
Square: dtoverlay=vc4-kms-dpi-hyperpixel4sq
```

## Add Expected Fonts to the RaspberryPi
Copy Genos-VariableFont_wght.ttf from the fonts folder to /usr/share/fonts
Then run
```
fc-cache -f -v
fc-list
```
Verify that Genos - Medium is in the list.
