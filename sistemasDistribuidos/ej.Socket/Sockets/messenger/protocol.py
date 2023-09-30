#!/usr/bin/env python3

import socket, sys, argparse

# TCP Sockect
# s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # TCP

def client(): 
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s: # socket UDP
        sending_data = struct.pack('!3sii','MUL'.encode(), 34, 54)
        s.sendto(sending_data, ('localhost', 1234))
        print ("Msg sended!")
       
def server():        
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  as s:# UDP
        # Create a tuple socket
        s.bind("", 1234)                                 # binding to port 1234 on 0.0.0.0
        msg = s.recvfrom(1024) # Size of message received is 1024 bytes
        op, n1, n2 = struct.unpack('!3sii', msg) # Unpack the message into a tuple
        op.decode() # Decode
        
        if op == 'SUM':
            result = f'{n1} + {n2} = {n1 + n2}'

parser = argparse.ArgumentParser()
parser.add_argument("-m", "--mode", choices=['server','client'],  type=str, help="client or server", default="server", required=False)

args = parser.parse_args()
server() if args.mode =="server" else client()
