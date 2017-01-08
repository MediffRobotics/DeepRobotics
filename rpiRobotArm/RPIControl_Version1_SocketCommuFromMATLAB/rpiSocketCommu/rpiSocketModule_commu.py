import time
import sys
import pandas as pd
sys.path.append("../rpiControllsArduinos/")
sys.path.append("../rpiSocketCommu/")
import SerialGpioControllArduinos 
import rpiSocketCommu_server

import SocketServer    
from SocketServer import StreamRequestHandler  
from time import ctime  
  
host = '192.168.0.16'#'172.16.0.155'#'166.111.198.234'#'166.111.198.85' 
#host = 'local'#'172.16.0.155'#'166.111.198.234'#'166.111.198.85' 
port = 30005
addr = (host,port)  
BUF_SIZE = 1024  
#SerialSendToArduino=SerialGpioControllArduinos.rpiControllArduinos()
#SerialSendToArduino=SerialGpioControllArduinos.rpiControllArduinos()
class Servers(StreamRequestHandler):
    df=pd.DataFrame()
    SerialSendToArduino=SerialGpioControllArduinos.rpiControllArduinos()
    
    def handle(self):  
        print 'connection from %s'%str(self.client_address)  
        self.wfile.write('connection %s:%s at %s succeed!' % (host,port,ctime()))
        
        while True:  
            try:  
                data = self.request.recv(1024)    
                if not data:                         
                    break  
                      
                self.ProcessingReceived(data)
      
                  
            except:  
                print "except data"  
        print "disconnect %s"%str(self.client_address)            
        
        
    def ProcessingReceived(self,data):
        #Print out data
        print "----\n%s\n[Recv]%s"%(str(self.client_address), data)
        
        if data.find(';')==-1 and data.find(',')==-1: #In teaching mode
            self.SerialSendToArduino.MoveSteps(data)
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
                self.SerialSendToArduino.MoveSteps(self.dfMove.ix[i,j])
                #time.sleep(1)
                
                print 'Move number: '+ str(k)   
                k=k+1 
                time.sleep(0.01)
                                
            while self.SerialSendToArduino.DetecAllENA()==0:
                time.sleep(0.01)
        

                                                          
            
              
print 'server is running....'    
server = SocketServer.ThreadingTCPServer(addr,Servers)    
server.serve_forever()   
print "Quit" 
