import os
import time
import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print ("Legam socketul...")

server_socket.bind(("0.0.0.0",6161))
print("Asteptam dupa clienti")
server_socket.listen(10)
print("Asteptam")
server_socket.accept()
print("Dormim")

time.sleep(100)