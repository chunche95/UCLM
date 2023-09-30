#!/usr/bin/env python3

###########################################################################################
# This is a simple TCP/IP server that listens for incoming connections
# 
# socket.socket() Crea un objeto socket que admite el tipo de administrador de contexto,
# para que pueda usarlo en una with statement. No es necesario llamar s.close()
###########################################################################################

import socket

HOST = '127.0.0.1'  # The server's hostname 
PORT = 65432        # The port used by the server 
try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT)) # Tupla doble: host y puerto
        s.listen() # Especifica que el servidor esta listo para recibir conexiones
        conn, addr = s.accept() # Método
        with conn: 
            print(f"Connected by {addr}")
            while True: # Se utiliza un bucle while infiniro para recorrer las llamadas del bloqueo a conn.recv()
                data = conn.recv(1024) # devuelve un objeto vacío de bytes pero con tamaño 1024 bytes
                if not data:
                    break
                print(f"Received {data.decode()}")
                conn.sendall(data) # Lee todos los datos que envía el cliente y los repite usando conn.sendall()
except socket.error as e:
    print(f"Socket error: {e}")    
except Exception as e:
    print(f"Exception: {e}")