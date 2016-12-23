import RPi.GPIO as GPIO
import time
import serial
import threading
import random
import pandas as pd
import sys
sys.path.append("../rpiDetectPushButtons/")
import RpiButtonDetectors

class rpiControllArduinos(threading.Thread):
        
        def __init__(self,baudrate=9600,PortNum="/dev/ttyACM0"):                                            
                #115200            
                #ENA Pin defination
                self.ArduEna_Base=29
                self.ArduEna_LowArm=31
                self.ArduEna_UpArm=33
                self.ArduEna_Wrist1=35
                self.ArduEna_Wrist2=37
                self.ArduEna_Wrist3=40
              
                GPIO.setmode(GPIO.BOARD)
                
                GPIO.setup(self.ArduEna_Base, GPIO.IN)
                GPIO.setup(self.ArduEna_LowArm, GPIO.IN)
                GPIO.setup(self.ArduEna_UpArm, GPIO.IN)
                GPIO.setup(self.ArduEna_Wrist1, GPIO.IN)
                GPIO.setup(self.ArduEna_Wrist2, GPIO.IN)
                GPIO.setup(self.ArduEna_Wrist3, GPIO.IN)
               
                print "Serial initialization... "
                
                
                self.port=serial.Serial(PortNum,baudrate,timeout=0)
                time.sleep(3)
                self.port.readall() #clear serial buffer
                
                #Init Button class
                self.ButtonStatus=RpiButtonDetectors.RpiRobotArmButtons()
                self.ButtonStatus.setDaemon(True)
                self.ButtonStatus.start()
                # Init threading
                threading.Thread.__init__(self)
                print "done. "
                
                # Init moving data
                self.strMove_a='0a'
                self.strMove_b='0b'
                self.strMove_c='0c'
                self.strMove_d='0d'
                self.strMove_e='0e0e'
                self.strMove_f='0f'   
                                
                self.intReverseMove_a=0
                self.intReverseMove_b=0
                self.intReverseMove_c=0
                self.intReverseMove_d=0
                self.intReverseMove_e=0
                self.intReverseMove_f=0
                
                self.intFinal_ReverseMove_a=0
                self.intFinal_ReverseMove_b=0
                self.intFinal_ReverseMove_c=0
                self.intFinal_ReverseMove_d=0
                self.intFinal_ReverseMove_e=0
                self.intFinal_ReverseMove_f=0  
                
                self.ProcessedSerialData=\
                    pd.DataFrame([self.strMove_a,self.strMove_b,self.strMove_c,\
                    self.strMove_d,self.strMove_e,self.strMove_f]).T
                
                self.OnTeachingFlag=0
        
        def DetectBaseENA(self):				
                #print "Base ENA: ",GPIO.input(self.ArduEna_Base)
                return GPIO.input(self.ArduEna_Base)
                
        def DetectUpArmENA(self):				
                #print "DetectUpArmENA: ",GPIO.input(self.ArduEna_Base)
                
                return GPIO.input(self.ArduEna_UpArm)        
                
        def DetectLowArmENA(self):				
                #print "DetectLowArmENA: ",GPIO.input(self.ArduEna_LowArm)
                return GPIO.input(self.ArduEna_LowArm)  
                
        def DetectWrist1ENA(self):				
                #print "DetectWrist1ENA: ",GPIO.input(self.ArduEna_Wrist1)
                return GPIO.input(self.ArduEna_Wrist1)
                
        def DetectWrist2ENA(self):				
                #print "DetectWrist2ENA: ",GPIO.input(self.ArduEna_Wrist2)
                return GPIO.input(self.ArduEna_Wrist2)
                
        def DetectWrist3ENA(self):				
                #print "DetectWrist3ENA: ",GPIO.input(self.ArduEna_Wrist2)
                return GPIO.input(self.ArduEna_Wrist3)                
                
        def DetecAllENA(self):
                if self.DetectBaseENA() == self.DetectUpArmENA()\
                   ==self.DetectLowArmENA() ==self.DetectWrist1ENA()\
                   ==self.DetectWrist2ENA()==self.DetectWrist3ENA()==1:
                       #print "All motors have done"
                       return True                       
                else:
                    #print "At least one motor has not done"
                    return False        
                                                           
        def MoveSteps(self,NumSteps):		
                self.port.write(NumSteps)
                time.sleep(0.01) # wait for a while,to let data receive                
                #while self.DetecAllENA()==0:					
                #    time.sleep(0.02) # wait
                #    print 'wait for done...'
                    
                #print 'Done for one move'
        def RecordingMoveBack(self,periodData='20',MotorTag='a'):   
            
            try:                 
                intPeriodData=int(periodData)
                                    
            except:
                print 'exception occourd, return: '
                print periodData
                print MotorTag
                
                return
            
            if(intPeriodData==0):
                return
                                
            Sign=intPeriodData/abs(intPeriodData)
            
            if MotorTag=='a':
                if(abs(intPeriodData)>=50):
                    self.intReverseMove_a=Sign*10+self.intReverseMove_a
                else :

                    self.intReverseMove_a=Sign*500+self.intReverseMove_a                               
            if MotorTag=='b':
                if(abs(intPeriodData)>=50):

                    self.intReverseMove_b=Sign*10+self.intReverseMove_b
                else :

                    self.intReverseMove_b=Sign*500+self.intReverseMove_b
                    
            if MotorTag=='c':
                if(abs(intPeriodData)>=50):

                    self.intReverseMove_c=Sign*10+self.intReverseMove_c
                else :

                    self.intReverseMove_c=Sign*500+self.intReverseMove_c
            if MotorTag=='d':
                if(abs(intPeriodData)>=50):

                    self.intReverseMove_d=Sign*10+self.intReverseMove_d
                else :

                    self.intReverseMove_d=Sign*500+self.intReverseMove_d
            if MotorTag=='e':
                if(abs(intPeriodData)>=50):

                    self.intReverseMove_e=Sign*10+self.intReverseMove_e
                else :

                    self.intReverseMove_e=Sign*500+self.intReverseMove_e
            
            if MotorTag=='f':
                if(abs(intPeriodData)>=50):

                    self.intReverseMove_f=Sign*10+self.intReverseMove_f
                else:

                    self.intReverseMove_f=Sign*500+self.intReverseMove_f
                    
                  
        def ProcessingReceived(self,data):                                                                   
                                                                                               
            List_data=data.split(';')
                                 
            #if not pressed button,concate to one row                             
            for i in List_data: 
                                                                       
                if  i.find('a')>-1: #In teaching mode
                    self.RecordingMoveBack(i[0:-1],i[-1])
                    
                    self.strMove_a=self.strMove_a+';'+i
                    #print 'append a'
                    
                    #for reseting motor 
                                                            
                if  i.find('b')>-1: #In teaching mode
                    self.strMove_b=self.strMove_b+';'+i                    
                    #print 'append b'
                    
                    self.RecordingMoveBack(i[0:-1],i[-1])

                    
                if  i.find('c')>-1: #In teaching mode
                    self.strMove_c=self.strMove_c+';'+i
                    #print 'append c'
                    self.RecordingMoveBack(i[0:-1],i[-1])

                if  i.find('d')>-1: #In teaching mode
                    self.strMove_d=self.strMove_d+';'+i
                    #print 'append d'
                    self.RecordingMoveBack(i[0:-1],i[-1])

                if  i.find('e')>-1: #In teaching mode
                    self.strMove_e=self.strMove_e+';'+i
                    #print 'append e'
                    self.RecordingMoveBack(i[0:-1],i[-1])

                if  i.find('f')>-1: #In teaching mode
                    self.strMove_f=self.strMove_f+';'+i
                    #print 'append f'                                                  
                    self.RecordingMoveBack(i[0:-1],i[-1])
                                                    
        def ProcessingPushButtons(self):
           
            if self.ButtonStatus.FlagPress_TeachingButton==1: #check for teaching flag  
                # start teaching, reset all variables                        
                print "start teaching"
                
                self.strMove_a='0a'
                self.strMove_b='0b'
                self.strMove_c='0c'
                self.strMove_d='0d'
                self.strMove_e='0e0e'
                self.strMove_f='0f'
                
                self.ProcessedSerialData=\
                    pd.DataFrame([self.strMove_a,self.strMove_b,self.strMove_c,\
                    self.strMove_d,self.strMove_e,self.strMove_f]).T
                    
                '''
                self.ProcessedSerialData=self.ProcessedSerialData.append\
                    (pd.DataFrame([self.strMove_a,self.strMove_b,self.strMove_c,\
                    self.strMove_d,self.strMove_e,self.strMove_f]).T)
                '''    
                
                self.OnTeachingFlag=1                                                                           
                self.ButtonStatus.FlagPress_TeachingButton=0
          
            elif self.ButtonStatus.FlagPress_InsertMovementButton==1: # checking insert new move
                
                self.UpdateFinalReverseMove()                                
                # append data 
                self.ProcessedSerialData=self.ProcessedSerialData.append\
                    (pd.DataFrame([self.strMove_a,self.strMove_b,self.strMove_c,\
                    self.strMove_d,self.strMove_e,self.strMove_f]).T)  
                           
                # reset passed data,prepare for next move
                self.strMove_a='0a'
                self.strMove_b='0b'
                self.strMove_c='0c'
                self.strMove_d='0d'
                self.strMove_e='0e'
                self.strMove_f='0f'
                                
                #Get received data and processing it  
                print "Inserted a new movement "
                print self.ProcessedSerialData                                                
                    
                self.ButtonStatus.FlagPress_InsertMovementButton=0
                                                                    
            elif self.ButtonStatus.FlagPress_PlayResetButton==1:# Play/reset button
                              
                #if pressed teaching button, saving data,doing reversing                
                if (self.OnTeachingFlag==1):
                    print 'start to move arm to origion'
                    self.MoveMotorsReversly()
                                       
                    #Appending reverse move                    
                    self.AppendingReverseMove()

                    # save data                    
                    self.SaveMoveData()                                    
                    self.ButtonStatus.FlagPress_PlayResetButton=0
                    self.OnTeachingFlag=0
                    
                    # Moving motor reversely
                                                         
                #else, loading data, send data and move command to controllers
                else:   
                    print "start to move arm based on recorded data"  
                                                  
                    self.LoadMoveData()  
                    self.SendingMoveDataToMotors()                                                                                        
                    self.ButtonStatus.FlagPress_PlayResetButton=0 
                    
                                                                                                                
        def SendingMoveDataToMotors(self):
            
            NumMoves=len(self.ProcessedSerialData)
            NumJoints=6
            for i in range(NumMoves):
                
                time.sleep(0.8) 
                                
                splited_move_a=(self.ProcessedSerialData.iat[i,0]).split(';')
                splited_move_b=(self.ProcessedSerialData.iat[i,1]).split(';')
                splited_move_c=(self.ProcessedSerialData.iat[i,2]).split(';')
                splited_move_d=(self.ProcessedSerialData.iat[i,3]).split(';')
                splited_move_e=(self.ProcessedSerialData.iat[i,4]).split(';')
                #splited_move_e=("0e".split(';'))
                splited_move_f=(self.ProcessedSerialData.iat[i,5]).split(';')                          
                
                CountFinishedMotor=[0,0,0,0,0,0]
                IndexMotorMove=0
                zeroCounter=0;
                while True:
                                                                                
                    try:
                        if splited_move_a[IndexMotorMove][0]=='0':
                            zeroCounter= zeroCounter+1
                        else:    
                            self.port.write(splited_move_a[IndexMotorMove])                                
                            #print splited_move_a[IndexMotorMove]
                            
                    except:
                        CountFinishedMotor[0]=1
                        
                    try:
                        
                        if splited_move_b[IndexMotorMove][0]=='0':
                            zeroCounter= zeroCounter+1
                        else:    
                            self.port.write(splited_move_b[IndexMotorMove])                                
                            #print splited_move_b[IndexMotorMove]
                            
                    except:
                        CountFinishedMotor[1]=1
                        
                    try:
                        if splited_move_c[IndexMotorMove][0]=='0':
                            zeroCounter= zeroCounter+1
                        else:    
                            self.port.write(splited_move_c[IndexMotorMove])                                
                            #print splited_move_c[IndexMotorMove]
                            
                    except:
                        CountFinishedMotor[2]=1
                        
                    try:
                        
                        if splited_move_d[IndexMotorMove][0]=='0':
                            zeroCounter= zeroCounter+1
                        else:    
                            self.port.write(splited_move_d[IndexMotorMove])                                
                            #print splited_move_d[IndexMotorMove]
                            
                    except:
                        CountFinishedMotor[3]=1
                      
                      
                    try:
                        if splited_move_e[IndexMotorMove][0]=='0':
                            zeroCounter= zeroCounter+1
                        else:    
                            self.port.write(splited_move_e[IndexMotorMove])                                
                            #print splited_move_e[IndexMotorMove]
                            
                            
                    except:
                        CountFinishedMotor[4]=1
                    
                    try:
                        
                        
                        if splited_move_f[IndexMotorMove][0]=='0':
                            zeroCounter= zeroCounter+1
                        else:    
                            self.port.write(splited_move_f[IndexMotorMove])                                
                            #print splited_move_f[IndexMotorMove]                        
                        
                        #time.sleep(0.01)
                    except:
                        CountFinishedMotor[5]=1
                                
                                    
                    if (sum(CountFinishedMotor)==6):    
                        break
                    
                    
                    stuckCounter=0
                    
                    while self.DetecAllENA()==True and (zeroCounter <= 5): # wait until all ena pins get low
                     
                        #time.sleep(0.01)                        
                        #print 'self.DetecAllENA(): '
                        #print self.DetecAllENA()
                        #break   
                        stuckCounter=stuckCounter+1
                        if(stuckCounter==100):
                            break
                        
                          
                        pass
                        #print "Stuck True"
                        #break
                    ####################################
                
                     
                    while self.DetecAllENA()==False and (zeroCounter <= 5): # wait until all ena pins get low
                        pass   
                        #print "Stuck False"
                        #time.sleep(0.01)
                        
                    #print 'zeroCounter: '
                    #print zeroCounter     
                    zeroCounter=0                        
                    IndexMotorMove=IndexMotorMove+1
                    
                    #time.sleep(0.5) 
            
                        
        def MoveMotorsReversly(self):            
            
            self.port.write(str(-self.intFinal_ReverseMove_a)+'A')  
            print str(-self.intFinal_ReverseMove_a)+'A'                      
            time.sleep(0.01)
            
            self.port.write(str(-self.intFinal_ReverseMove_b)+'B') 
            print str(-self.intFinal_ReverseMove_b)+'B'           
            time.sleep(0.01)
            
            print str(-self.intFinal_ReverseMove_c)+'C'
            self.port.write(str(-self.intFinal_ReverseMove_c)+'C')            
            time.sleep(0.01)
            
            self.port.write(str(-self.intFinal_ReverseMove_d)+'D')
            print str(-self.intFinal_ReverseMove_d)+'D'
            time.sleep(0.01)
            
            self.port.write(str(-self.intFinal_ReverseMove_e)+'E')
            print str(self.intFinal_ReverseMove_e)+'E'
            time.sleep(0.01)
            
            self.port.write(str(-self.intFinal_ReverseMove_f)+'F')
            print str(-self.intFinal_ReverseMove_f)+'F'
            time.sleep(0.01)
                    
        def SaveMoveData(self):                            
            
            self.ProcessedSerialData.to_csv('MoveData.csv',index=False)
            print "all data is saved"
        
        def LoadMoveData(self): 
            self.ProcessedSerialData=pd.read_csv('MoveData.csv') 
            
        def UpdateFinalReverseMove(self):
            
            self.intFinal_ReverseMove_a=self.intFinal_ReverseMove_a+self.intReverseMove_a
            self.intFinal_ReverseMove_b=self.intFinal_ReverseMove_b+self.intReverseMove_b
            self.intFinal_ReverseMove_c=self.intFinal_ReverseMove_c+self.intReverseMove_c
            self.intFinal_ReverseMove_d=self.intFinal_ReverseMove_d+self.intReverseMove_d
            self.intFinal_ReverseMove_e=self.intFinal_ReverseMove_e+self.intReverseMove_e
            self.intFinal_ReverseMove_f=self.intFinal_ReverseMove_f+self.intReverseMove_f
            
            self.intReverseMove_a=0
            self.intReverseMove_b=0
            self.intReverseMove_c=0
            self.intReverseMove_d=0
            self.intReverseMove_e=0
            self.intReverseMove_f=0 
            
            
        def AppendingReverseMove(self):
            
                
            self.ProcessedSerialData=self.ProcessedSerialData.append\
                    (pd.DataFrame(
                    [str(-self.intFinal_ReverseMove_a)+'A'\
                    ,str(-self.intFinal_ReverseMove_b)+'B'\
                    ,str(-self.intFinal_ReverseMove_c)+'C'\
                    ,str(-self.intFinal_ReverseMove_d)+'D'\
                    ,str(-self.intFinal_ReverseMove_e)+'E'\
                    ,str(-self.intFinal_ReverseMove_f)+'F'\
                    ]).T)
                    
                    
            self.intReverseMove_a=0
            self.intReverseMove_b=0
            self.intReverseMove_c=0
            self.intReverseMove_d=0
            self.intReverseMove_e=0
            self.intReverseMove_f=0                                     
            
            self.intFinal_ReverseMove_a=0
            self.intFinal_ReverseMove_b=0
            self.intFinal_ReverseMove_c=0
            self.intFinal_ReverseMove_d=0
            self.intFinal_ReverseMove_e=0
            self.intFinal_ReverseMove_f=0   
            
        def run(self):
            
            while 1:
                #Processing received data                
                Data=self.port.readall()
                if(self.OnTeachingFlag==1):                    
                    if Data!='':
                        self.ProcessingReceived(Data) 
                        #print self.serialData
                
                time.sleep(0.3) 
                                 
                #Processing push buttons
                self.ProcessingPushButtons();                          
            
        def CloseSerial(self):
                self.port.close()
                

if __name__=='__main__':
                          
        ############################
        
        SerialSendToArduino=rpiControllArduinos()                    
        SerialSendToArduino.setDaemon(True)
        SerialSendToArduino.start()
        #SerialSendToArduino.LoadMoveData()
        #SerialSendToArduino.SendingMoveDataToMotors()
        time.sleep(5000)
        while True:
            pass
                                    
        print 'sending data'
        

      
