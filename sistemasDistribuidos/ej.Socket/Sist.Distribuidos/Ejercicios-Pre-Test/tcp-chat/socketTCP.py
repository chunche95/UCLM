import socket
import struct
import random
import string

def server():
    # Crear un socket UDP
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Dirección y puerto del servidor
    server_address = ('localhost', 12345)

    # Enlazar el socket a la dirección y puerto del servidor
    server_socket.bind(server_address)

    print("Servidor escuchando en {}:{}".format(*server_address))

    while True:
        # Recibir datos del cliente
        data, client_address = server_socket.recvfrom(1024)

        # Decodificar los datos recibidos
        length = struct.unpack('!H', data[:2])[0]
        message = data[2:].decode('utf-8')

        print("Mensaje recibido de {}: {}".format(client_address, message))
        print("Longitud del mensaje:", length)

def client():
    # Crear un socket UDP
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Dirección y puerto del servidor
    server_address = ('localhost', 12345)

    try:
        for numerMessages in range(20):
            # Generar una cadena aleatoria
            random_string = ''.join(random.choice(string.ascii_letters) for _ in range(10))

            # Calcular la longitud de la cadena aleatoria
            string_length = len(random_string)

            # Empaquetar los datos en un formato binario
            packed_data = struct.pack('!H', string_length) + random_string.encode('utf-8')

            # Enviar los datos al servidor
            client_socket.sendto(packed_data, server_address)

            print("Mensaje enviado al servidor:", random_string)

    except KeyboardInterrupt:
        print("Cliente finalizado por el usuario.")

if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser(description="Cliente y servidor UDP para enviar y recibir mensajes.")
    parser.add_argument("-m", "--mode", choices=['server', 'client'], type=str, help="Modo de funcionamiento: servidor o cliente", required=True)
    args = parser.parse_args()

    if args.mode == 'server':
        server()
    elif args.mode == 'client':
        client()
    else:
        print("Modo no válido. Use 'server' o 'client'.")
