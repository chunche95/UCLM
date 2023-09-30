#!/usr/bin/env python3

import socket, random, argparse, struct, string, sys


def main(mode):
    if mode == "server":
        server()
    elif mode == "client":
        for value in range(5):
            client()
    elif mode == "exit":
        print("Exiting...")
        sys.exit(0)         
    else:
        print("Invalid mode")

def client():    
    # Create a tuple socket
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client_socket: # socket UDP
        # Server address and port
        server = ('localhost', 65432)        
        try :
            # Connect to the server
            # client_socket.connect(server)
            # Generate a random string
            random_string =  ''.join(random.choice(string.ascii_letters) for _ in range(10))
            # Calculate the lentgh of the string
            string_length = len(random_string)
            # Pack the data into a binary format
            #package_data = struct.pack('!3sii', b'req', string_length, random_string.encode('utf-8'))
            package_data = struct.pack('!3sI{}s'.format(string_length), b'req', string_length, random_string.encode('utf-8'))

            # Send message pack
            client_socket.sendto(package_data, server)
            print ("Message sended!")
        except socket.error as e:
            print(e)
        
    
def server():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server_socket: # UDP
        # Create a tuple socket
        server_addr =('localhost',65432)
        # Bind the socket to the port
        server_socket.bind(server_addr)
        # Listen for incoming connections
        # server_socket.listen(1) # No es necesario en UDP para recibir datos de un cliente
        print("Server listening on {}:{}".format(*server_addr))
        # Receive data
        while True:            
            # Wait for a connection
            # print("Waiting for a connection...")
            # client_socket, client_address = server_socket.accept()
            # print("Connected to", client_address)
            try:
                # Receive the 16 bits integer indicating the length of the string
                # length_data = client_socket.recv(2)
                package_data, client_address = server_socket.recvfrom(1024)
                # if len(length_data) < 2:
                #    break   # Connection closed by client
                # Unpack the data into a integer
                #request, length, random_string_bytes = struct.unpack('!3sii', package_data)
                request, length = struct.unpack('!3sI', package_data[:7])
                random_string_bytes = package_data[7:]
                random_string = random_string_bytes.decode('utf-8')
                print("Mensaje recibido:", random_string)            
            except socket.error as e:
                print(e)
                

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Enviar mensajes al servidor y recibirlos de vuelta usando una cadena random")
    parser.add_argument("-m", "--mode", choices=['server', 'client', 'exit'], type=str, help="client, server or exit", default="server", required=False)
    args = parser.parse_args()
    main(args.mode)
