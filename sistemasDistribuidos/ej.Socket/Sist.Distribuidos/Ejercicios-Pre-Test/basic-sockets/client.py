#!/usr/bin/env python3

import socket, warnings

IP_SERVER = "172.29.194.5"
PORT_SERVER = 4080
# Mensajes a enviar al server
message=["Hi server!","I'm a client!","Nice to meet you!","My name is ñandú!","Well, bye!" ]
# Control de errores con warnings
#custom_warning = 'Warning: Message not ASCII. Message will be sent as UTF-8'

def is_ascii(s):
    return all(ord(c) < 128 for c in s)

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s: # socket UDP
    try :           
        for value in message:
            #s.sendto(b'Hello, world!', ('172.19.196.163', 4080))
            if value.lower() == 'exit':
                break
            #if is_ascii(value):
            #    s.sendto(value.encode('ascii') , (IP_SERVER,PORT_SERVER))
            #else:
            #warnings.warn(custom_warning)
            s.sendto(value.encode('utf-8') , (IP_SERVER,PORT_SERVER))            
            print(value)
    except socket.error as e:
        print(e)
print ("Bye server!")