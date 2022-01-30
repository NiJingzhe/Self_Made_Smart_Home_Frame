#encoding: utf-8
from . import error
from flask import render_template
from flask import request
from flask import redirect
from flask import url_for

@error.route('/lack_info_err_page')
def lack_info_err():
    return render_template('lack_info_err.html')

@error.route('/non-existent_device_del_err_page')
def non_existent_device_del_err():
    return render_template('non_existent_device_del_err.html')

@error.route('/repeatedly_add_device_err_page')
def repeatedly_add_device_err():
    return render_template('repeatedly_add_device_err.html')
