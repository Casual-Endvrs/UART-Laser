#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Feb 21 17:42:17 2021

@author: bobjoe
"""

from Arduino import Arduino

port = '/dev/ttyACM2'
baud = 9600

serial = Arduino(port, baud)
serial.connect()

while(True):
    usr = input("User input: ")
    serial.send_command(usr)
    response = serial.get_responses(num_responses=1)
    print( response )
    if usr == 'exit' :
        break

serial.disconnect()


