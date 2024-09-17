#!/usr/bin/env python3
import socket
import struct
import argparse

parser = argparse.ArgumentParser()

parser.add_argument(
    '-m', '--mode',
    type=str,
    choices=['server', 'client'],
    default='server',
    help='Choose server or client mode'
)

args = parser.parse_args()



def server():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind(('0.0.0.0', 5000))
        data = s.recv(1024)
        n1, n2  = struct.unpack('ii', data)
        result = n1 + n2
        print("{} + {} = {}".format(n1,n2,result))
def client():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        n1 = 4
        n2 = 3
        s.sendto(struct.pack('!ii', n1, n2), ('localhost', 5000))
              

exec_func = server if args.mode =='server' else client
exec_func()
