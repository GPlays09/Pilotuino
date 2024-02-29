# Pilotuino

This is a little Arduino development 'environment' I've made. It contains only the most necessary files to enable compiling and uploading to Arduino Leonardo and other 32u4-based Arduinos (only tested on Leonardo; you might need to add some variant files for others to work).

The majority of files were copied, over and some modified, from the Arduino IDE 1.8.x files, with the addition of some of my own, such as verify.bat, upload.bat, and files in the py\ dir.

The 'environment' is made so that the user_script.cpp must remain unchanged (location and name), or else you have to change the paths in the verify.bat and upload.bat.

## Features
I've made features like runtime COM port disabling and custom device descriptors, and I've also cleaned up some of the junk that is of no use to us. But the main reason I've made this is that you can easily mess around in here without affecting your main Arduino IDE installation (which is not required, except for the Arduino drivers for identification purposes, I think).

With that said, the features that I've implemented are controlled through the USBDevice.attach(...) function that I've modified; its definition can be found in the hardware\arduino\avr\cores\arduino\USBAPI.h.
The parameters should be self-explanatory, based on their names.

I've also included the py\search.py which when run from cmd will search recursively for a phrase you input as the first argument throughout all the files included in the hardware directory.


## Compiling
Run verify.bat, which will generate all the necessary files required for the Arduino to function, and upon closing the opened cmd window, it cleans up the build directory.

## Uploading
Run upload.bat before closing verify.bat's cmd window. The script that is run to handle uploading is py\upload.py. In a nutshell, it functions like this: if there is a device visible in the device manager that fits the usual vid and pid of the Arduino Leonardo and has a COM port open, it will do some stuff required and automatically upload the compiled sketch to your Arduino. If there isn't a device with said criteria, it will look for one for 10 seconds before exiting. If you don't have a COM port enabled and you want the script to upload, simply while it's looking for devices, press the reset button on your Leonardo, i.e., put it into the bootloader.
 
