from flask_sqlalchemy import SQLAlchemy as sqlal
from app import device_in_room


class home:

    def __init__(self, owner_):
        self.owner = owner_
        self.room_list = {}

    def add_room(self, room):
        if not (room.name in self.room_list.keys()):
            self.room_list[room.name] = room
        else:
            pass

    def del_room(self, room_name):
        if room_name in self.room_list.keys():
            del self.room_list[room_name]
        else:
            pass
