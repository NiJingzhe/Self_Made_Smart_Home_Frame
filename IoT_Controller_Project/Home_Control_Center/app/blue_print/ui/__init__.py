from flask import Blueprint
from .lib.home import home


ui = Blueprint('ui',__name__,template_folder = 'templates')
my_home = home(owner_="Lil-Dinosaur")

from . import views