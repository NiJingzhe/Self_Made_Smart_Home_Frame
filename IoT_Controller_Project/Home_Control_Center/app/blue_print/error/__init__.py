#encoding: utf-8
from flask import Blueprint

error = Blueprint('error',__name__,template_folder = 'templates')

from . import views
