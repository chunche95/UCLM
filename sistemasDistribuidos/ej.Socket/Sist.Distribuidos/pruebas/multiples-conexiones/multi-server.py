#!/usr/bin/env python3

import socket, sys, selectors, types, argparse

sel = selectors.DefaultSelector()

# Comprobación de argumentos y valores por default
def arguments():
    # Crear un objeto ArgumentParser
    parser = argparse.ArgumentParser(description="Programa de conexión con el servidor")
    # Agregar argumentos posicionales
    parser.add_argument("host", nargs='?', default='localhost', type=str, help="Argumento asignado a la dirección IP del servidor (opcional)")
    parser.add_argument("port", nargs='?', default=65432, type=int, help="Argumento asignado al puerto abierto del servidor (opcional)")
    # Agregar opciones (argumentos opcionales)
    parser.add_argument("-o", "--opcion", type=str, help="Descripción de la opción")
    # Parsear los argumentos de la línea de comandos
    args = parser.parse_args()    
    return args.host, args.port

def accept_wrapper(sock):
    conn, addr = sock.accept() # Método de recibir conexiones
    print(f"Conexión establecida con {addr}")
    conn.setblocking(False) # Configurar el socket del servidor como no bloqueante

    # Crear ub objeto para almacenar datos de cliente y eventos
    data = types.SimpleNamespace()
    data.addr = addr
    data.inb=b''
    data.outb = b''
    events = selectors.EVENT_READ | selectors.EVENT_WRITE
    sel.register(conn, events, data=data) # Registra el socket 

def service_connection(key, mask):
    sock = key.fileobj
    data = key.data

    if mask & selectors.EVENT_READ:
        recv_data = sock.recv(1024) # devuelve un objeto vacío de bytes pero con tamaño 1024 bytes
        if recv_data:
            print(f"Received {recv_data.decode('utf-8')}")
            data.outb += recv_data
        else:
            print(f"Conexión cerrada por {data.addr}")
            sel.unregister(sock)
            sock.close()
        if mask & selectors.EVENT_WRITE:
            if data.outb:
                sent = sock.sendall(data.outb) # Envía todos los datos que recibe el cliente y los repite usando conn.send
                data.outb = data.outb[sent:] # Lee todos los datos que envía el cliente y los repite usando conn.send

def main():
    try:
        HOST, PORT = arguments()
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind((HOST, PORT)) # Tupla doble: host y puerto
            s.listen() # Especifica que el servidor esta listo para recibir conexiones
            print(f"Servidor listo en {HOST}:{PORT}")
            s.setblocking(False) # Configurar el socket del servidor como no bloqueante
            sel.register(s, selectors.EVENT_READ, data=None) # Registra el socket 
            #conn, addr = s.accept() # Método de recibir conexiones
            #with conn: 
                #print(f"Connected by {addr}")                
            while True: # Se utiliza un bucle while infiniro para recorrer las llamadas del bloqueo a conn.recv()
                events = sel.select(timeout=0.5)
                for key, mask in events:
                    if key.data is None:
                        accept_wrapper(key.fileobj)
                        print(f"Accepted connection from {key.fileobj.getpeername()}") #
                    else:
                        service_connection(key, mask) # Método de recibir conexiones
                
    except socket.error as e:
        print(f"Socket error: {e}")    
    except Exception as e:
        print(f"Exception: {e}")

if __name__ == "__main__":
    main()
    