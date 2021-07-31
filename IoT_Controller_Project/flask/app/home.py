
class home:

    def __init__(self, owner_):
        self.owner = owner_
        self.device_list = {}

    def add_device(self, device):
        if not (device.name in self.device_list.keys()):
            self.device_list[device.name] = device.control_type

    def del_device(self, device_name):
        if device_name in self.device_list.keys():
            del self.device_list[device_name]
