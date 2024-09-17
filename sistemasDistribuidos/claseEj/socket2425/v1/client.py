#!/bin/python3

import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s.sendto(f'Hi {socket.AddressInfo}'.encode() , ('localhost', 12345))