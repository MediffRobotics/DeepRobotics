#!/usr/bin/python
import socket
HOST='192.168.0.16'
PORT=3000
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((HOST,PORT))  
while 1:
       cmd=raw_input("Please input cmd:")      
       s.sendall(cmd)     
       data=s.recv(1024)    
       print data       
s.close()  
