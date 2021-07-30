from app import app
from flask_sqlalchemy import SQLAlchemy as sqlal

db = sqlal(app)


class device_in_room(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    room_name = db.Column(db.String(255))
    device_name = db.Column(db.String(255))
    control_type = db.Column(db.String(255))

    def __init__(self, device_name, control_type, room_name):

        self.room_name = room_name
        self.device_name = device_name
        self.control_type = control_type

    def __repr__(self):

        return '<Device %r %r>' % self.device_name % self.control_type
