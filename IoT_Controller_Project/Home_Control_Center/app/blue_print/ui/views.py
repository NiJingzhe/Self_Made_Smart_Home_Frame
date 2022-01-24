#encoding: utf-8
from . import ui
from . import my_home
from .lib.device import device
from flask import render_template
from flask import request
from flask import redirect
from flask import url_for
import json,requests

@ui.route('/', methods=['GET', 'POST'])
@ui.route('/index', methods=['GET', 'POST'])
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

                return redirect(url_for('error.lack_info_err'))

        elif request.form['button'] == "删除设备":

            my_home.del_device(request.form['device_name'])

            return render_template('home.html', owner_name=my_home.owner,
                                   device_list_=my_home.device_list)

        elif request.form['button'] in my_home.device_list:

            return redirect(url_for('ui.device_page', device_name=request.form['button'],
                                    control_type=my_home.device_list[request.form['button']]))

    else:

        return render_template('home.html', owner_name=my_home.owner,
                               device_list_=my_home.device_list)


@ui.route('/device/<device_name>/<control_type>', methods=['GET', 'POST'])
def device_page(device_name, control_type):

    # broadcast and get device state from Device_Controller
    headers = {
        'content-type': "application/json;charset=UTF-8",
        #'dahai-access-token': 'SQwNSp',
        #'x-trailer-biz-product-line': 'k12'
    }
    #如果配置了nginx+uwsgi的生产环境，端口号按照nginx配置写
    #my nginx is running on port 80,so I write :80 here,
    #if you want to run this code by "flask run",then you should write :5000
    api = "http://"+"127.0.0.1:80"+url_for('api.api_send_command_to_device')
    #POST请求
    post_args = {"device_name":device_name,"command":"get_state"}
    re=requests.post(api,
                    params = post_args,
                    headers=headers, verify=False)
    
    print('\n \n',"ui print: re.text is: ",re.text,'\n \n')

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

                post_args = {"device_name":device_name,"command":"open"}
                re=requests.post(api,
                                params = post_args,
                                headers=headers, verify=False)
                result = json.loads(re.text)["result"]

                if result == "no feedback":
                    return "no feedback, please check the device!"
                elif not (result["task_state"] == "finished" or result["device_state"] == u"打开"):
                    #print('\n \n',"ui print: device_state not match on open",'\n \n')
                    return "some error occured when device process the task, please check the device!"
                else:
                    device_state = result["device_state"]
                    switch_value = "关闭"

                return render_template("switch.html", state=device_state, device_name=device_name,value=switch_value)

            elif request.form['button'] == "关闭":

                post_args = {"device_name":device_name,"command":"close"}
                re=requests.post(api,
                                params = post_args,
                                headers=headers, verify=False)

                result =json.loads(re.text)["result"]

                if result == "no feedback":
                    return "no feedback, please check the device!"
                elif not (result["task_state"] == "finished" or result["device_state"] == u"关闭"):
                    #print('\n \n',"ui print: device_state not match on close",'\n \n')
                    return "some error occured when device process the task, please check the device!"
                else:
                    device_state = result["device_state"]
                    switch_value = "打开"

                return render_template("switch.html", state=device_state, device_name=device_name,value=switch_value)
            elif request.form['button'] == "返回控制中心":
                return redirect(url_for('ui.home_page'))
        else:
            return render_template("switch.html", state=device_state, device_name=device_name,value=switch_value)


    elif control_type == "switch&slider":
        return ""