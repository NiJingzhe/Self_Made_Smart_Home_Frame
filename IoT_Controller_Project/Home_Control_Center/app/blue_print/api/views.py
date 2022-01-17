from . import api
import json,requests
from flask import request
from . import my_receiver
from . import my_sender



@api.route('/api/send_command_to_device',methods=['POST'])
def api_send_command_to_device():

    if len(request.args) == 0:
        return json.dumps({"result":"no args!"}).encode('utf-8')

    get_data = request.args

    command_message = {"device_name":get_data["device_name"].encode('utf-8'),"command":get_data["command"].encode('utf-8')}
    my_sender.broadcast(command_message)

    times = 0
    feedback_message = my_receiver.receive()
    print("api print: feedback_message is: ",feedback_message,'\n \n')
    while (feedback_message == False) and (times < 10):
        feedback_message = my_receiver.receive()
        times += 1
        print("api print: feedback_message is: ",feedback_message)

    if feedback_message == False:
        return json.dumps({"result":"no feedback!"}).encode('utf-8')
    else:
        return json.dumps(feedback_message).encode('utf-8')
