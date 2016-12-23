#!/usr/bin/python
import socket   
import commands   

class SocketCommu:
	def __init__(self,Host='172.16.0.155',Port=30006):
		print "initing socket communication"		
		self.SockHost=Host
		self.SockPort=Port
		self.SockObj=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		#self.SockObj.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1) 
		self.SockObj.bind((self.SockHost,self.SockPort))  
		  
		#self.ListenSock()			
							
	def ListenSock(self):
		self.SockObj.listen(1)
		#self.conn,self.addr=self.SockObj.accept()
		#self.SockObj.setblocking(0)
		#print 'Connected by',self.addr   

	def AcceptSock(self):
		self.SockObj.listen(1)			  
		self.conn,self.addr=self.SockObj.accept()
		self.SockObj.setblocking(0)
		
		print 'Connected by',self.addr  
		
		data=self.conn.recv(1024)
		

		print 'Received data: ',data
		return data
		 
	def CloseSocket(self):		  
		self.conn.close()     

if __name__=='__main__':
	print 'Sample demo'
			
	socketCommObj=SocketCommu()
		
	while 1:
			
		socketCommObj.AcceptSock()
			
	socketCommObj.CloseSocket()	
		
