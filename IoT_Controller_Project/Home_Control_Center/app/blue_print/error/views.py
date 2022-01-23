#encoding: utf-8
from . import error
from flask import render_template
from flask import request
from flask import redirect
from flask import url_for

@error.route('/lack_info_err_page')
def lack_info_err():
    return render_template('lack_info_err.html')
