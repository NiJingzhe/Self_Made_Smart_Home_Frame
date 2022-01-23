#encoding: utf-8
from flask import Blueprint
from .lib.sender import sender
from .lib.receiver import receiver

api = Blueprint('api',__name__,template_folder = 'templates')
my_sender = sender(HOST_IP='255.255.255.255',PORT=4000)
my_receiver = receiver(PORT=4001)

from . import views