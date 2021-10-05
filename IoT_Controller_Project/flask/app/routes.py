# 从app模块中即从__init__.py中导入创建的app应用
from app import app
from flask import render_template
from flask import request
from flask import redirect
from flask import url_for
from app.home import home
from app.device import device
from app.sender import sender
from app.receiver import receiver
import requests
import json


my_home = home(owner_="Lil-Dinosaur")
my_sender = sender(HOST_IP='192.168.12.255',PORT=4000)
my_receiver = receiver(PORT=4001)



# 建立路由，通过路由可以执行其覆盖的方法，可以多个路由指向同一个方法。

###__________________________________________________________________
#      UI


@app.route('/', methods=['GET', 'POST'])
@app.route('/index', methods=['GET', 'POST'])
def home_page():

    if request.method == 'POST':

        if request.form['button'] == "添加设备":

            if ("control_type" in request.form.keys()) and ("device_name" in request.form.keys() and (request.form['device_name'] != '')):
                device_ = device(request.form['device_name'],
                                 request.form['control_type'])

                my_home.add_device(device_)

                return render_template('home.html', owner_name=my_home.owner,
                                       device_list_=my_home.device_list)
            else:

                return redirect(url_for('lack_info_err'))

        elif request.form['button'] == "删除设备":

            my_home.del_device(request.form['device_name'])

            return render_template('home.html', owner_name=my_home.owner,
                                   device_list_=my_home.device_list)

        elif request.form['button'] in my_home.device_list:

            return redirect(url_for('device_page', device_name=request.form['button'],
                                    control_type=my_home.device_list[request.form['button']]))

    else:

        return render_template('home.html', owner_name=my_home.owner,
                               device_list_=my_home.device_list)


@app.route('/device/<device_name>/<control_type>', methods=['GET', 'POST'])
def device_page(device_name, control_type):

    # broadcast and get device state from Device_Controller
    headers = {
        'content-type': "application/json;charset=UTF-8",
        'dahai-access-token': 'SQwNSp',
        'x-trailer-biz-product-line': 'k12'
    }
    
    api = "http://"+"127.0.0.1:5000"+url_for('api_send_command_to_device')
    #POST请求
    post_args = {"device_name":device_name,"command":"get_state"}
    re=requests.post(api,
                    params = post_args,
                    headers=headers, verify=False)
    
    ##print("\n \n \n \n \n "+re.text+" \n \n \n \n")

    feedback_message=json.loads(re.text)

    device_state = feedback_message["result"]["device_state"]
    if feedback_message["result"]["device_value"] != "":
        device_value = feedback_message["device_value"]


    if control_type == "switch":
        
        if device_state == "打开":
            switch_value = "关闭"
        else:
            switch_value = "打开"

        if request.method == "POST":
            if request.form['button'] == "打开":
                '''  command_message = {"device_name":device_name,"cmd":"open"}
                    my_sender.broadcast(command_message) ''' 

                post_args = {"device_name":device_name,"command":"open"}
                re=requests.post(api,
                                params = post_args,
                                headers=headers, verify=False)
                result = json.loads(re.text)["result"]

                if result == "no feedback":
                    return "no feedback, please check the device!"
                elif not (result["task_state"] == "finished" and result["device_state"] == "打开"):
                    return "some error occured when device process the task, please check the device!"
                else:
                    device_state = result["device_state"]
                    switch_value = "关闭"

                return render_template("switch.html", state=device_state, device_name=device_name,value=switch_value)
            elif request.form['button'] == "关闭":
                '''command_message = {"device_name":device_name,"cmd":"close"}
                my_sender.broadcast(command_message)'''

                post_args = {"device_name":device_name,"command":"close"}
                re=requests.post(api,
                                params = post_args,
                                headers=headers, verify=False)

                result =json.loads(re.text)["result"]

                if result == "no feedback":
                    return "no feedback, please check the device!"
                elif not (result["task_state"] == "finished" and result["device_state"] == "关闭"):
                    return "some error occured when device process the task, please check the device!"
                else:
                    device_state = result["device_state"]
                    switch_value = "打开"

                return render_template("switch.html", state=device_state, device_name=device_name,value=switch_value)
            elif request.form['button'] == "返回控制中心":
                return redirect("/index")
        else:
            return render_template("switch.html", state=device_state, device_name=device_name,value=switch_value)


    elif control_type == "switch&slider":
        return ""

###__________________________________________________________________
#      Error



@app.route('/lack_info_err_page')
def lack_info_err():
    return render_template('lack_info_err.html')


###__________________________________________________________________
#      WebAPI

@app.route('/api/send_command_to_device',methods=['POST'])
def api_send_command_to_device():

    if len(request.args) == 0:
        return json.dumps({"result":"no args!"}).encode('utf8')

    get_data = request.args

    command_message = {"device_name":get_data["device_name"],"command":get_data["command"]}
    my_sender.broadcast(command_message)

    times = 0
    feedback_message = my_receiver.receive()
    while (feedback_message == False) and (times < 100):
        feedback_message = my_receiver.receive()
        times += 1

    if feedback_message == False:
        return json.dumps({"result":"no feedback!"}).encode('utf-8')
    else:
        return json.dumps(feedback_message).encode('utf-8')


