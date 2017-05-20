#!/usr/bin/env python2.7
import socket
# Trimite pachete broadcast

_port = 10000

import sys, time
from socket import *

sock = socket(AF_INET, SOCK_DGRAM)
sock.bind(('', 0))
sock.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
print 

while True:
    data = repr(time.time()) + '\n'
    print('ana are mere : %s' % data)
    sock.sendto(data, ('10.3.3.255', _port))
    time.sleep(2)
