#!/usr/bin/env python3

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # socket UDP
s.sendto(b'Hello, world!', ('127.0.0.1', 1234)
s.close()        