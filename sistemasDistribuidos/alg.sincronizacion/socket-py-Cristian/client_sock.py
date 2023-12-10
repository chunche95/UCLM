#!/bin/python3
import socket
import datetime

from dateutil import parser 
from timeit import default_timer as timer

# function used to sync client process time
def syncTime():
    csock = socket.socket()

    # server port number
    port = 4080

    # connect to the clock server on remote ip
    csock.connect(('192.168.8.224', port))

    requestTime = timer()

    # receive date from server
    serverTime = parser.parse(csock.recv(1024).decode())
    responseTime = timer()
    actualTime = datetime.datetime.now()

    print("Time return by server: " + str(serverTime))

    processDelayLatency = responseTime - requestTime

    print("Process delay latency by server: " + str(processDelayLatency) +  " seconds")
    print("Actual clock time al client side: " + str(actualTime))

    # sync process client clock time
    clientTime = serverTime + datetime.timedelta(seconds = (processDelayLatency) / 2)

    print("Sync process client time: " + str(clientTime))

    # calculate sync error
    error = actualTime - clientTime
    print("Sync error: " + str(error) + " seconds")
    csock.close()
# driver function
if __name__ == "__main__":
    # sync time usring clock server
    syncTime()