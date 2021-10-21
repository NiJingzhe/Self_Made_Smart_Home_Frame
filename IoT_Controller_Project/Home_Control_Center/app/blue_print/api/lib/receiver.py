import socket
import json

class receiver:

    ss = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    PORT = 4001


    def __init__(self, PORT):
        self.ss.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        self.ss.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR, 1)
        self.ss.bind(('', PORT))


    def receive(self):
        message, address = self.ss.recvfrom(65535)
        if not len(message):
            return False
        else:
            data = json.loads(message.decode('utf-8'))
            return data

    
