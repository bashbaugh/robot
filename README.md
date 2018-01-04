# robot
code for the robot i am building, based off the donkey car   (http://www.donkeycar.com/)


# How to manually install donkey on raspbian wheezy

follow the instructions at http://www.donkeycar.com/faq/how-do-i-manually-install-the-software-on-raspberry-pi,
but instead of typing "sudo pip3 install tensorflow-0.12.1-cp34-cp34m-linux_armv7l.whl", 
type:

sudo apt-get install python3.4
python3.4 -m pip install tensorflow-0.12.1-cp34-cp34m-linux_armv7l.whl

then follow the rest of the instructions.
### Please note:
I haven't tested  this yet, but because of python 3.4 and 3.5 conflicts, you might have to replace all
'pip3 install's with 'python3.4 -m pip install'.
