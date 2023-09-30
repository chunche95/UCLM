#!/usr/bin/env python3

import socket

# TCP Sockect
# s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # TCP

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
# Create a tuple socket
s.bind("", 1234)                                 # binding to port 1234 on 0.0.0.0
msg, addr = s.recvfrom(1024) # Size of message received is 1024 bytes
s.close()
print(msg.decode())
