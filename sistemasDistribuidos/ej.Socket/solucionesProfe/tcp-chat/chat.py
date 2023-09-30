#!/usr/bin/env python3

import socket, sys, argparse

class Messenger:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # self.sock.connect((self.host, self.port))
    
    def exit_request(self, msg):
        return msg.lower() == 'exit'
    
    def send_msg(self):
        msg = input("Tu: ")
        self.sock.send(msg.encode())
        if self.exit_request(msg): self.close()
    
    def recv_msg(self):
        msg = self.sock.recv(1024).decode()
        print(f"Otro: {msg}")
        if self.exit_request(msg): self.close()
    
    def close(self):
        print("Cerrando conexion ...")
        self.sock.close()
        sys.exit(0)

class Client(Messenger):
    def __init__(self, host, port):
        super().__init__(host, port)
    
    def start(self):
        self.sock.connect((self.host, self.port))

        while True:
            self.send_msg()
            self.recv_msg()

class Server(Messenger):
    def __init__(self, host, port):
        super().__init__(host, port)

    def bind(self):
        self.sock.bind((self.host, self.port)) # tupla
        self.sock.listen(5)            
    
    def start(self):
        self.bind()
        self.sock, addr = self.sock.accept()
        print(f" Conexion establecida con {addr}")

        while True:
            self.recv_msg()
            self.send_msg()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-c",'--client', action='store_true') # Habilitar la bandera para el modo cliente
    parser.add_argument("-i", '--host', type=str, default='127.0.0.1') # Dirección IP del servidor
    parser.add_argument("-p", '--port', type=int, default=5000) # Puerto del servidor
    args = parser.parse_args()
    # Determina si el programa se ejecutará en modo cliente o servidor
    messenger_class = Client if args.client else Server
    messenger = messenger_class(args.host, args.port)
    messenger.start() # Inicia la comunicación del cliente o servidor
