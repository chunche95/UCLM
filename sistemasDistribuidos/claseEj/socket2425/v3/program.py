#!/usr/bin/env python3
import socket
import argparse

def server():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind(('0.0.0.0', 5000))

        while True:
            data, addr = s.recvfrom(1024)
            print(f"Received {data.decode()} from {addr[0]}:{addr[1]}")

            response = f"Echo: {data.decode()}"
            s.sendto(response.encode(), addr)
        print(f"Received {data.decode()} from {addr.encode()}")
def client():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.sendto(f'Hi {socket.AddressInfo}'.encode() , ('localhost', 5000))        

parser = argparse.ArgumentParser()

parser.add_argument(
    '-m' , '--mode',
    type = str,
    choices = ['server', 'client'],
    default = 'server',
    help = 'Choose server or client mode'
)

args = parser.parse_args()
exec_func = server if args.mode == 'server' else client 
exec_func()
