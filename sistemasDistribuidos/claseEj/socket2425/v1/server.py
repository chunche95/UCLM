#!/bin/python3

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('0.0.0.0', 12345))
msg = s.recv(1024)
print(f"{msg.decode()}")