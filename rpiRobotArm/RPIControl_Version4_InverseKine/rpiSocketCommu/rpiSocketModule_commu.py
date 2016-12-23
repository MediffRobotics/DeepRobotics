import time
import sys
import pandas as pd
import SocketServer
import threading
import socket

    
from SocketServer import StreamRequestHandler  
from time import ctime  
  
host = '169.254.138.189'
port = 30005
portClient=30004
addr = (host,port)  
BUF_SIZE = 1024  

GloReceived=''


class Servers(StreamRequestHandler):
    df=pd.DataFrame()
    
    def handle(self): 
        global GloReceived; 
        print 'connection from %s'%str(self.client_address)  
        self.wfile.write('connection %s:%s at %s succeed!' % (host,port,ctime()))
        
        while True:  
            try:  
                data = self.request.recv(1024)    
                if not data:                         
                    break  
                 
                print "received data" 
                print data
                GloReceived=data;      
                #self.ProcessingReceived(data)
                                        
            except:  
                print "except data"  
        print "disconnect %s"%str(self.client_address)            
        
   
    def ProcessingReceived(self,data):
        #Print out data
        print "----\n%s\n[Recv]%s"%(str(self.client_address), data)
        
        if data.find(';')==-1 and data.find(',')==-1: #In teaching mode
            #self.SerialSendToArduino.MoveSteps(data)
            print data
            return 0
            
            
        
        split_data=data.split(';')        

        for i in split_data:
            
            if i!='':  #Check for invalid data          
                
                j=i.split(',')
                
                if j[0] == 'finish': #check for finish flag
                    print j
                    print 'Finished for receiving data,saving it.'                    
                    self.df.to_csv('MoveData.csv')#,index=False,header=False)
                    self.dfMove=self.df
                    self.df=pd.DataFrame()  # Clear buffer
                    
                elif j[0] == 'start': 
                    print 'Starting To MoveArm.' 
                    self.StartingToMoveArm()
                    
                    
                else :                                        
                    df_temp=pd.DataFrame(j)
                    self.df=self.df.append(df_temp.T,ignore_index=True)    
                    
                    print self.df
                    
    def StartingToMoveArm(self):
        #dfMove=pd.read_csv('MoveData.csv',header=None)
        print 'Staring to move'
        print self.dfMove
        
        NumRows=self.dfMove.shape[0]
        NumCols=self.dfMove.shape[1]
                
        
        k=0
                  
        for i in range(NumRows):
            for j in range(NumCols):
                
                print self.dfMove.ix[i,j]
                #self.SerialSendToArduino.MoveSteps(self.dfMove.ix[i,j])
                
                print self.dfMove.ix[i,j]
                #time.sleep(1)
                
                print 'Move number: '+ str(k)   
                k=k+1 
                time.sleep(0.01)
                                
            #while self.SerialSendToArduino.DetecAllENA()==0:
                time.sleep(0.01)
                
class socketCommuWithMatlab(threading.Thread):
    def __init__(self):       
        threading.Thread.__init__(self);
        self.server = SocketServer.ThreadingTCPServer(addr,Servers)
        pass
    
        #client
        self.s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)      
        print "connecting"
        self.s.connect(('169.254.177.40',3004))      
        print "connected"
    
    def sendingTo(self):
        while 1:
            cmd=raw_input("Please input cmd:")    
            self.s.sendall(cmd)     
            data=self.s.recv(1024)     
        print data         
        s.close()     
    def run(self):
       
        print 'server is running....'                
        self.server.serve_forever()   
        print 'server is finished....' 
 
    def asas(self):
        #global GloReceived  
        print "transferd data: "
        print GloReceived                
if __name__=='__main__':
                
    
    sockMatlab=socketCommuWithMatlab()
    #sockMatlab.setDaemon(True)
    #sockMatlab.start()
    sockMatlab.sendingTo()
    '''
    for i in range(10):
        sockMatlab.asas()
        time.sleep(1)
    '''
    time.sleep(10)
    print "Quit" 
    
