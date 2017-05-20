#!/usr/bin/env python2.7
import sys
import socket


sock=socket.socket(socket.AF_INET ,socket.SOCK_STREAM )
sock.connect(('localhost',10000))


if len(sys.argv) == 2:
             message = sys.argv[1]
else:
             message = 'ana are mere'
try:
    sock.sendall(message)
finally:
    sock.close()
