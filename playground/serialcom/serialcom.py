#!/usr/bin/python3
# Based on https://forum.arduino.cc/index.php?topic=396450.0 and 
#          https://forum.arduino.cc/index.php?topic=225329.msg1810764#msg1810764


def sendToArduino(sendStr):
    ser.write(sendStr.encode('utf-8'))

def recvFromArduino():
    global startMarker, endMarker
    
    result = ""
    response = "z" # any value that is not an end- or startMarker
    
    # wait for the start character
    while ord(response) != startMarker: 
        response = ser.read(1)
    
    # save data until the end marker is found
    while ord(response) != endMarker:
        if ord(response) != startMarker:
          result = result + response.decode("utf-8")
        response = ser.read(1)
    
    return result

def waitForArduino():

    # wait until the Arduino sends 'Arduino Ready' - allows time for Arduino reset
    # it also ensures that any bytes left over from a previous message are discarded
    
    global startMarker, endMarker
    
    msg = ""
    while msg.find("Arduino is ready") == -1:

        while ser.inWaiting() == 0:
            pass
        
        msg = recvFromArduino()

        print (msg) 
        print ()

#======================================
# DEMO PROGRAM
#======================================

import serial
import time

# NOTE the user must ensure that the serial port and baudrate are correct
serPort = "/dev/ttyUSB0"
baudRate = 9600
ser = serial.Serial(serPort, baudRate)
print ("Serial port " + serPort + " opened  Baudrate " + str(baudRate))

startMarker = 60 # <
endMarker = 62   # >

waitForArduino()

waitingForReply = False
name = ""

while name != 'quit':
    name = input("Data (type 'quit' to exit) --> ")

    if name == 'quit':
        print("Exiting...")
        break

    if ord(name[0]) != startMarker or ord(name[-1]) != endMarker:
        print("Wrong input")
        continue

    if waitingForReply == False:
        sendToArduino(name)
        print ("Sent from PC to Arduino --> " + name)
        waitingForReply = True

    if waitingForReply == True:
        print ("WAITING...")

        while ser.inWaiting() == 0:
            pass
        
        dataRecvd = recvFromArduino()
        print ("Reply Received --> " + dataRecvd)
        waitingForReply = False

        print ("=========== READY ===========")

    time.sleep(1)

ser.close
