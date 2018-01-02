import serial
arduino = serial.Serial('/dev/ttyUSB1', 9600)
arduino.baudrate = 9600

while True:
    print(arduino.readline())
