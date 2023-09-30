#!/usr/bin/env python3

import socket, struct, random 

words= ['abc', 'bcd random', 'cde', 'defgh', 'ñéndu  por aquí']
word = random.choice(words).encode()
size = len(words)
format = f'!h{str(size)}s'

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client:
    data = struct.pack(format, len(word), word)
    msg = client.sendto(data, ('127.0.0.1', 9000)) 
    print(msg, data.decode())