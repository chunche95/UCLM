#!/usr/bin/env python3

import socket, sys, argparse

# TCP Sockect
# s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # TCP

parser = argparse.ArgumentParser()
parser.add_argument("-m", "--mode", type=str, help="client or server", default="server", required=False)


args = parser.parse_args()
mode = args.mode

if mode == "client":    
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s: # socket UDP
        s.sendto(b"Hello, world!", ('127.0.0.1', 1234))
        print ("Hello, world sended!")
        sys.exit(0)
        
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  as s:# UDP
    # Create a tuple socket
    s.bind("", 1234)                                 # binding to port 1234 on 0.0.0.0
    msg, addr = s.recvfrom(1024) # Size of message received is 1024 bytes

print(msg.decode())