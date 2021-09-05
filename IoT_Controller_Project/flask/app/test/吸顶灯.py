# udp_gb_client.py
'''客户端（UDP协议局域网广播）'''

import socket
import json

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)

device_name = "吸顶灯"
SENDPORT = 4001
RECVPORT = 4000
state = "关闭"

s.bind(('', RECVPORT))
print('Listening for broadcast at ', s.getsockname())

while True:

    data, address = s.recvfrom(65535)
    message = json.loads(data.decode('utf-8'))
    print('message received from Server{}:{}'.format(address, data.decode('utf-8')))
    
    if message['device_name'] == device_name:
        
        if message['cmd'] == "get_state":
            s.sendto(json.dumps({"state":state}).encode('utf-8'),(address[0],SENDPORT))
        if message['cmd'] == "close":
            state = "关闭"
        if message['cmd'] == "open":
            state = "打开"
        print("自身状态： ",state)
