from app.__init__ import device_in_home
from app.__init__ import db
class home:

    def __init__(self, owner_):
        self.owner = owner_
        self.device_list = {}

    def add_device(self, device):
        if not (device.name in self.device_list.keys()):
            dev = device_in_home(device.name,device.control_type)
            db.session.add(dev)
            db.session.commit()
            self.device_list[device.name] = device.control_type
            

    def del_device(self, device_name):
        if device_name in self.device_list.keys():
            dev = device_in_home.query.filter_by(device_name = device_name).first()
            db.session.delete(dev)
            db.session.commit()
            del self.device_list[device_name]
            
