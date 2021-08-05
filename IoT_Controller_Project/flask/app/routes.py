# 从app模块中即从__init__.py中导入创建的app应用
from app import app
from flask import render_template
from flask import request
from flask import redirect
from flask import url_for
import time
import sys
from app.home import home
from app.device import device


my_home = home(owner_="Lil-Dinosaur")

# 建立路由，通过路由可以执行其覆盖的方法，可以多个路由指向同一个方法。


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
    return ""


@app.route('/lack_info_err_page')
def lack_info_err():
    return render_template('lack_info_err.html')
