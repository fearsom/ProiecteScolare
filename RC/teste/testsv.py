
#!/usr/bin/env python2.7

import sys
import socket

sock=socket.socket(socket.AF_INET ,socket.SOCK_STREAM)
sock.bind(('localhost',10000))
sock.listen(1)

while True:
    print 'w8ing conn'
    conn,server_adress=sock.accept()
    try:
        print 'recieved data', server_adress
        while True;
        data=conn.recv(1024)
        print 'message "%s" ',%data
        if not data:
            break


    finally:
        conn.close()
        
