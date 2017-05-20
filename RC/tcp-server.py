#!/usr/bin/env python2.7

import socket
import sys


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('localhost', 10000))
sock.listen(1)

while True:
	print 'waiting for a connection'
	connection, client_address = sock.accept()

	try:
		print 'connection from', client_address
		while True:
			data = connection.recv(1024)
			print >>sys.stderr, 'received "%s"' % data
			if not data:
				break
	finally:
		connection.close()

