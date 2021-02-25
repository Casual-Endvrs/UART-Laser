#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Feb 21 17:42:17 2021

@author: bobjoe
"""

from Arduino import Arduino

port = '/dev/ttyACM0'
baud = 115200

serial = Arduino(port, baud)

print( serial.get_avail_ports() )

serial.connect()

print( serial.arduino )

while(True):
    uC_message = serial.get_responses(num_responses=1)
    if uC_message is False :
        continue
    uC_message = uC_message.strip()
    print( f'message: |{uC_message}|' )
    if uC_message == "End of Setup" :
        break

serial.flush_buffer()

while(True):
    usr = input("User input: ")
    if usr=="clr" :
        serial.arduino.flush()
        continue
    serial.send_command(usr)
    response = serial.get_responses(num_responses=1)
    print( response )
    if usr == 'exit' :
        break

serial.flush_buffer()
serial.disconnect()


