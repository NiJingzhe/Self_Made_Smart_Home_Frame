class home:

    def __init__(self,owner_):
        self.owner = owner_
        self.room_list = {}

    def add_room(self,room):
        self.room_list[room.name] = room
        
    def del_room(self,room_name):
        if room_name in self.room_list.keys():
            del self.room_list[room_name]
        else:
            pass