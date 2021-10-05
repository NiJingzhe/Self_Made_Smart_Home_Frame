import socket
import json


class sender:

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    PORT = 4000
    HOST = '192.168.255.255'

    def __init__(self, HOST_IP, PORT):
        self.HOST = HOST_IP
        PORT = PORT
        self.s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        self.s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR, 1)

    def broadcast(self, message):
        self.s.sendto(json.dumps(message).encode('utf-8'),
         (self.HOST, self.PORT))



