#encoding: utf-8
from . import api
import json,requests
from flask import request
from . import my_receiver
from . import my_sender
from ...model import device_in_home
from ...model import db


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

#DB operator api
@api.route('/api/get_device_info',methods = ['POST'])
def api_get_device_info():

    device_list = []

    device_list = device_in_home.query.all()
    result_dict = {}

    if device_list != []:
        
        result_dict["device_num"] = len(device_list)
        for i in range(0,len(device_list)):
            device_dict = {}
            device_dict["device_name"] = device_list[i].device_name
            device_dict["control_type"] = device_list[i].control_type
            result_dict[i] = device_dict
    else:
        result_dict['device_num'] = 0

    return json.dumps({"result":result_dict})


@api.route('/api/write_to_db',methods = ['POST'])
def api_write_to_db():

    if len(request.args) == 0:
        return json.dumps({"result":"no args!"})

    get_data = request.args

    if device_in_home.query.filter_by(device_name=get_data['device_name']).first() == None:
        device_log = device_in_home(get_data['device_name'],get_data['control_type'])
        db.session.add(device_log)
        db.session.commit()
        return json.dumps({"result":"add successfully"})
    else:
        return json.dumps({"result":"failed! Repeatedly add the same device!"})

@api.route('/api/del_from_db',methods = ['POST'])
def api_del_from_db():

    if len(request.args) == 0:
        return json.dumps({"result":"no args!"})
    
    get_data = request.args

    if  device_in_home.query.filter_by(device_name=get_data['device_name']).first() != None:
        device_log = device_in_home.query.filter_by(device_name=get_data['device_name']).first()
        db.session.delete(device_log)
        db.session.commit()
        return json.dumps({"result":"delet successfully"})
    else:
        return json.dumps({"result":"failed! A non-existent log cannot be deleted!"})