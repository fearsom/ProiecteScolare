#!/usr/bin/env python2.7

import socket
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.sendto('ana are mere', ('10.11.8.162', 10000))

