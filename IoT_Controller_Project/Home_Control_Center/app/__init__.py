#encoding: utf-8
from flask import Flask
import os
#from flask_sqlalchemy import SQLAlchemy as sqlal


def create_app():

    app = Flask(__name__)

    '''basedir = os.path.abspath(os.path.dirname(__file__))
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'Home_Info.db')
    app.config['SQLALCHEMY_MIGRATE_REPO'] = os.path.join(basedir, 'db_repository')
    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True '''

    from .blue_print.ui import ui
    app.register_blueprint(ui)
    from .blue_print.error import error
    app.register_blueprint(error)
    from .blue_print.api import api
    app.register_blueprint(api)

    #db = sqlal(app) 

    app.app_context().push()

    return app

app = create_app()


