from flask import Flask
import os


app = Flask(__name__)

basedir = os.path.abspath(os.path.dirname(__file__))
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'Home_Info.db')
app.config['SQLALCHEMY_MIGRATE_REPO'] = os.path.join(basedir, 'db_repository')

from app import routes

from flask_sqlalchemy import SQLAlchemy as sqlal

db = sqlal(app)


class device_in_home(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    device_name = db.Column(db.String(255))
    control_type = db.Column(db.String(255))

    def __init__(self, device_name, control_type):

        self.device_name = device_name
        self.control_type = control_type

    def __repr__(self):

        return '<Device %r %r>' % self.device_name % self.control_type





