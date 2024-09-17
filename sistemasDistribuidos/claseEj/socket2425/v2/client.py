#!/usr/bin/env python3

import socket 

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    s.send("Hello!".encode())
    data, addr = s.recvfrom(1024)
    print(f"Received {data.decode()} from {addr[0]}:{addr[1]}")
           