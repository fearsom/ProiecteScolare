#!/usr/bin/env python2.7

import socket

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind(('', 10000))



while True:

    data, addr = sock.recvfrom(1024)
    print('mesaj primit %s de la %s')%(data,addr)
