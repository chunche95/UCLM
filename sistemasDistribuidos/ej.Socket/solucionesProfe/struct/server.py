#!/usr/bin/env python3

import socket, struct 

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server:
    server.bind(('127.0.0.1', 9000))
    while True:
        data, addr = server.recvfrom(1024)
        SIZE, = struct.unpack('!h', data[:2])
        word, = struct.unpack('!'+ str(1) + 's', data[2:])
        print(f' Got "word.decode()" ({1} bytes)')
        server.sendto(data, addr)