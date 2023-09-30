import unittest
import socket
import threading
import time
import random
import string

class TestUDPServerClient(unittest.TestCase):
    def setUp(self):
        # Iniciar el servidor en un hilo separado
        self.server_thread = threading.Thread(target=self.start_server)
        self.server_thread.daemon = True
        self.server_thread.start()
        time.sleep(1)  # Esperar a que el servidor se inicie

    def start_server(self):
        # Crear un socket UDP para el servidor
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # Dirección y puerto del servidor
        server_address = ('localhost', 12345)

        # Enlazar el socket a la dirección y puerto del servidor
        self.server_socket.bind(server_address)

        while True:
            data, _ = self.server_socket.recvfrom(1024)
            self.last_received_message = data.decode('utf-8')

    def test_client_sends_message_to_server(self):
        # Crear un socket UDP para el cliente
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # Dirección y puerto del servidor
        server_address = ('localhost', 12345)

        # Mensaje de prueba
        valid_chars = string.ascii_letters + string.digits + string.punctuation
        message = random_string = ''.join(random.choice(valid_chars) for _ in range(1024))

        # Enviar el mensaje al servidor
        client_socket.sendto(message.encode('utf-8'), server_address)

        # Esperar a que el servidor reciba y procese el mensaje
        time.sleep(1)

        # Comprobar si el mensaje fue recibido correctamente por el servidor
        self.assertEqual(self.last_received_message, message)

    def tearDown(self):
        # Cerrar el socket del servidor
        self.server_socket.close()

if __name__ == '__main__':
    unittest.main()
