#从app模块中即从__init__.py中导入创建的app应用
from app import app
from flask import render_template
from flask import request
from flask import redirect
from flask import url_for
import sys
from app.home import home 
from app.device import device
from app.room import room

my_home = home(owner_ = "Lil-Dinosaur")

#建立路由，通过路由可以执行其覆盖的方法，可以多个路由指向同一个方法。
@app.route('/', methods=['GET','POST'])
@app.route('/index', methods=['GET','POST'])
def index():
    if request.method=='POST':

        if request.form['button'] == "添加房间":

            room_ = room(request.form['room_name'])                     
            my_home.add_room(room_)                                
            return render_template('index.html',home_name=my_home.owner,       
                                room_list_ = my_home.room_list)

        elif request.form['button'] == "删除房间":

            my_home.del_room(request.form['room_name'])
            return render_template('index.html',home_name=my_home.owner,
                                room_list_ = my_home.room_list)
        else:

            return redirect(url_for('roomPage',
                            room_name = request.form['button']))
            
    else:

        return render_template('index.html',home_name=my_home.owner,
                              room_list_ = my_home.room_list)
    
    
@app.route('/room/<room_name>', methods=['GET','POST'])
def roomPage(room_name):

    if request.method == 'POST':
        
        if request.form['button'] == "添加设备":

            device_ = device(request.form['device_name'],
                            request.form['control_type'])

            my_home.room_list[room_name].add_device(device_)

            return render_template('room.html',room_name_=room_name,
                                device_list_=my_home.room_list[room_name].device_list)
                                
        elif request.form['button'] == "删除设备":

            my_home.room_list[room_name].del_device(request.form['device_name'])

            return render_template('room.html',room_name_=room_name,
                                device_list_=my_home.room_list[room_name].device_list)
                                
        else:
            
            pass
        
    else:
    
        return render_template('room.html',room_name_=room_name,
                                device_list_=my_home.room_list[room_name].device_list)





