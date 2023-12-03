#!/bin/python3
import socket
import datetime

# Function user to initiate the clock server
def initiateClockServer():
    
    ssock = socket.socket() # Socket socket 
    print("Socket successfully established") 
    
    sport = 8001 # Server port number 
    ssock.bind(('localhost', sport)) # Socket server address and port number to connect 

    # Start listening for requests
    ssock.listen(5) # Start listening for requests
    print("Listening for requests...")
    # clock server running ever 
    while True:
        # establish connection with client
        connection, address = ssock.accept()
        print("Server connected to", address)
        # Respond the client with server clock time
        connection.send(str(datetime.datetime.now()).encode()) # Send server clock time 
        # close connection with the client process
        connection.close()
# driver function 
if __name__ == '__main__':
    # trigger the clock server 
    initiateClockServer()
