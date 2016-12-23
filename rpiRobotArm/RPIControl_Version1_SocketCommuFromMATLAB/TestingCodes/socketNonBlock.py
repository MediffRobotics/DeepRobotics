

import SocketServer    
from SocketServer import StreamRequestHandler  
from time import ctime  
  
host = '172.16.0.155' 
port = 30005
addr = (host,port)  
BUF_SIZE = 1024  
  
class Servers(StreamRequestHandler):    
    def handle(self):  
        print 'connection from %s'%str(self.client_address)  
        #self.wfile.write('connection %s:%s at %s succeed!' % (host,port,ctime()))    
        while True:  
            try:  
                data = self.request.recv(1024)    
                if not data:     
                    print "no data" 
                    break    
                print "----\n%s\n[Recv]%s"%(str(self.client_address), data)  
                self.request.send(data)  
            except:  
                print "except data"  
        print "disconnect %s"%str(self.client_address)  
              
print 'server is running....'    
server = SocketServer.ThreadingTCPServer(addr,Servers)    
server.serve_forever()   
print "Quit" 






'''
import socket
import threading
import SocketServer

class ThreadedTCPRequestHandler(SocketServer.BaseRequestHandler):

    def handle(self): 
        data = self.request.recv(1024)  
        cur_thread = threading.current_thread()
        response = "{}: {}".format(cur_thread.name, data)
        print "Server received: ", data
        self.request.sendall(response)
        
    def sendToClient(self):    
        self.request.sendall("Server auto send")
        
class ThreadedTCPServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    
    print "thread tcp"
    pass

def client(ip, port, message):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))
    try:
        #sock.sendall(message)
        response = sock.recv(1024)
        print "client Received: {}".format(response)
    finally:
        sock.close()

if __name__ == "__main__":
    # Port 0 means to select an arbitrary unused port
    HOST, PORT = "localhost", 0

    server = ThreadedTCPServer((HOST, PORT), ThreadedTCPRequestHandler)
    ip, port = server.server_address

    # Start a thread with the server -- that thread will then start one
    # more thread for each request
    server_thread = threading.Thread(target=server.serve_forever)
    # Exit the server thread when the main thread terminates
    server_thread.daemon = True
    server_thread.start()
    print "Server loop running in thread:", server_thread.name

    client(ip, port, "Hello World 1")
    #client(ip, port, "Hello World 2")
    #client(ip, port, "Hello World 3")

    server.shutdown()
    server.server_close()
'''

