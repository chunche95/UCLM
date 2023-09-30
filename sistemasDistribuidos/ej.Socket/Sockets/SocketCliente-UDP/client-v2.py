#!/usr/bin/env python3

import socket

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s: # socket UDP
    s.sendto(b'Hello, world!', ('127.0.0.1', 1234)
print ("Hello, world sended!")