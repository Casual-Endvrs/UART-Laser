#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Feb 21 17:42:22 2021

@author: bobjoe
"""

from Arduino import Arduino

port = '/dev/ttyACM0'
baud = 9600

serial = Arduino(port, baud)
serial.connect()

while(True):
    uC_message = serial.get_responses(num_responses=1).strip()
    print( uC_message )
    if uC_message == 'exit' or uC_message==False :
        break

serial.disconnect()
