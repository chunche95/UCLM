#!/bin/python3

from functools import reduce
from dateutil import parser

import threading
import datetime
import socket
import time

clientData = {}

def startReceiveClockTime(conn, add):
    while True:
        clockTimeString = conn.recv(1024).decode()
        clockTime = parser.parse(clockTimeString)
        clockTimeDiff = datetime.datetime.now() - clockTime

        clientData[add] =  {
            "clock time "    : clockTime,
            "time differece" : clockTimeDiff,
            "connector "     : conn
        }

        print("Client data updated with: " + str(add) + " clock time: " + str(clockTime),  end = "\n\n")
        time.sleep(3)

def startConnecting(master):
    while True:
        masterSlaveConn, addr = master.accept()
        slaveAddr = str(addr[0]) + ":" + str(addr[1])
        print("Master connected to slave: " + slaveAddr, end = "\n\n")
        print(slaveAddr + " got connected successfully")
        currentThread = threading.Thread(target = startReceiveClockTime, args = (masterSlaveConn, slaveAddr))

        currentThread.start()

def getAverageClockDiff():
    currentClientData = clientData.copy()
    timeDiffList = list(client['time differece'] 
                        for clientAddr, client in clientData.items())
    
    sumOfClockDiff = sum(timeDiffList, datetime.timedelta(0,0))

    averageClockDiff = sumOfClockDiff / len(clientData)
    return averageClockDiff

def syncAllClock():
    while True:
        print("New sync started")
        print("Number of client to be sync: " + str(len(clientData)))

        if len(clientData) > 0:
            averageClockDiff = getAverageClockDiff()
            for clientAddr, client in clientData.items():
                try:
                    syncTime = datetime.datetime.now() + averageClockDiff
                    client['connector'].send(str(syncTime).encode())
                except Exception as e:
                    print("Exception occured while sync clock: " + str(e))
        else :
            print("No client to sync")
        
        print("\n\n")
        time.sleep(5)

def initiateClockServer():
    master = socket.socket()
    print("Socket successfully established")
    port = 8001

    master.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Socket server address and port number to connect a master server
    print("Socket at master node created successfully")

    master .bind(('localhost', port)) # Start listening for requests

    master.listen(5) # Start listening for requests
    print("Listening for requests...")

    print("Starting to make connections with slaves")
    masterThread = threading.Thread(target = startConnecting, args = (master, )) # Start connecting with slaves
    masterThread.start() 

    syncThread.start() # Start syncing clock with slaves

if __name__ == '__main__':
    syncThread = threading.Thread(target = syncAllClock) # Start syncing clock with slaves
    initiateClockServer() # Trigger the clock server
    