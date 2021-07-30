from flask_sqlalchemy import SQLAlchemy as sqlal
from app import device_in_room


class room:

    def __init__(self, name):
        self.name = name
        self.device_list = {}

    def add_device(self, device):
        if not (device.name in self.device_list.keys()):
            self.device_list[device.name] = device.control_type


    def del_device(self, device_name):
        if device_name in self.device_list.keys():
            del self.device_list[device_name]
        else:
            pass
