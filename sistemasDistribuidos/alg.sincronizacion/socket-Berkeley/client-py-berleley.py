#!/bin/python3

from timeit import default_timer as timer
from dateutil import parser

import threading
import datetime
import socket
import time

def startSendTime(slave):
    while True:
        slave.send(str(datetime.datetime.now()).encode()) # provide server with clock time at the client        
        print("Recent time sent successfully",end = "\n\n")
        time.sleep(3)
        print("Recent time sent successfully", end = "\n\n")
        time.sleep(1)

def startReceiveTime(slave):
    while True:
        # receive data from server
        syncTime = parser.parse(slave.recv(1024).decode())
        print(" Sync time at the client: " + str(syncTime), end = "\n\n")

def initiateSlaveClient():
    port=8001 # port number
    slaveClient = socket.socket() # socket object to connect
    # Connect to the clock server on local computer
    slaveClient.connect(('localhost', port))
    # Start sending time to server
    print("Starting to receive time from server \n")
    sentTimeThread = threading.Thread(target = startSendTime, 
                                      args = (slaveClient,))
    sentTimeThread.start()

    print("Starting to receiving sync time gfrom server \n")
    receiveTimeThread = threading.Thread(target = startReceiveTime, 
                                         args = (slaveClient,))
    receiveTimeThread.start()

if __name__ == '__main__':
    initiateSlaveClient()
   
