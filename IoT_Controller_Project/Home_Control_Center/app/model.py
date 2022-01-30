#encoding: utf-8
from flask_sqlalchemy import SQLAlchemy as sqlal
from .db import db


class device_in_home(db.Model):
    device_name = db.Column(db.String(255), unique=True, primary_key=True)
    control_type = db.Column(db.String(255))

    def __init__(self, device_name, control_type):

        self.device_name = device_name
        self.control_type = control_type

    def __repr__(self):

        return '<Device %r %r>' % self.device_name % self.control_type