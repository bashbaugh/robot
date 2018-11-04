# Robot
Code for the robot i am building, based off the donkey car   (http://www.donkeycar.com/)


The `arduino` folder contains the code for the arduino on my robot. `arduino/two_wheel_robot/src/two_wheel_robot.ino` is the current version. It simply takes commands
from the raspberry pi and uses them to control the L298N motor driver. It also takes input from two ir sensors positioned at the front of the robot and uses them to
avoid obstacles that the raspberry pi misses.

`Config.py` is the file whcih contains the values needed for the raspberry pi to send the right commands to the arduino. `~/d2/config.py` on the rpi should be 
replaced with this file.

`actuator.py` contains the class `two_wheel_arduino` for sending signals to the arduino. it should replace `donkey/donkeycar/parts/actuator.py`

in `d2/manage.py`, replace all mentoins of `PCA9685` with `two_wheel_arduino`.

### Please note:

This code is somewhat outdated, unorganized, and hard-to-understand, so you'll probably run into less frustration if you just write your own. Feel free to ask me for help!

