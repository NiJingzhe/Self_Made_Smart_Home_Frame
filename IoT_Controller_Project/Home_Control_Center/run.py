#encoding: utf-8
#从app模块中导入app应用
from flask import Flask
from app import app
from app.db import db
from app.model import device_in_home

#防止被引用后执行，只有在当前模块中才可以使用
if __name__=='__main__':
    app.run()
    db.session.delete(device_in_home.query.all())
