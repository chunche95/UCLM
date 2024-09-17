#!/usr/bin/env python3

import socket

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    s.bind(('0.0.0.0', 5000))

    while True:
        data, addr = s.recvfrom(1024)
        print(f"Received {data.decode()} from {addr[0]}:{addr[1]}")

        response = f"Echo: {data.decode()}"
        s.sendto(response.encode(), addr)
    print(f"Received {data.decode()} from {addr.encode()}")