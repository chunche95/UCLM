#!/usr/bin/env python3

import socket, warnings

IP_SERVER = '172.29.194.5'
PORT_SERVER = 4080
# Control de errores con warnings
custom_warning = 'Warning: Message not ASCII. Message will be sent as UTF-8'

def is_ascii(s):
    return all(ord(c) < 128 for c in s)


s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
# Create a tuple socket
s.bind((IP_SERVER,PORT_SERVER)) # binding to port 1234 on localhost
msg, addr = s.recvfrom(1024) # Size of message received is 1024 bytes
print("Bye client!")
s.close()
if is_ascii:    
    print(custom_warning)
    pass
print(msg.decode('ascii'))

