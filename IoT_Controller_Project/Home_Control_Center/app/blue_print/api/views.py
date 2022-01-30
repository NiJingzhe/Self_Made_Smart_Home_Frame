#encoding: utf-8
from . import api
import json,requests
from flask import request
from . import my_receiver
from . import my_sender
from .lib.Data_Base import device_in_home
from app import db

#向指定设备发送指令
@api.route('/api/send_command_to_device',methods=['POST'])
def api_send_command_to_device():

    if len(request.args) == 0:
        return json.dumps({"result":"no args!"})

    get_data = request.args

    command_message = {"device_name":get_data["device_name"],"command":get_data["command"]}
    my_sender.broadcast(command_message)

    times = 0
    feedback_message = my_receiver.receive()
    print("api print: feedback_message is: ",feedback_message,'\n \n')
    while (feedback_message == False) and (times < 10):
        feedback_message = my_receiver.receive()
        times += 1
        print("api print: feedback_message is: ",feedback_message)

    if feedback_message == False:
        return json.dumps({"result":"no feedback!"})
    else:
        return json.dumps(feedback_message)

@api.route('/api/write_to_db',method = ['POST'])
def api_write_to_db():

    if len(request.args) == 0:
        return json.dumps({"result":"no args!"})

    get_data = request.args
    device_log = device_in_home(get_data['device_name'],get_data['control_type'])
    db.session.add(device_log)
    db.commit()
    return json.dumps({"result":"add successfully"})

@api.route('/api/del_from_db',method = ['POST'])
def api_del_from_db():

    if len(request.args) == 0:
        return json.dumps({"result":"no args!"})
    
    get_data = request.args
    device_log = device_in_home.query.filter_by(username=get_data['device_name'])
    db.session.delete(device_log)
    db.commit()
    return json.dumps({"result":"delet successfully"})