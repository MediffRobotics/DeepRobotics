import RPi.GPIO as GPIO
import time
import serial

class rpiControllArduinos:
        def __init__(self,baudrate=9600,PortNum="/dev/ttyACM0"):
                #ENA Pin defination
                self.ArduEna_Base=29
                self.ArduEna_LowArm=31
                self.ArduEna_UpArm=33
                self.ArduEna_Wrist1=35
                self.ArduEna_Wrist2=37
                self.ArduEna_Wrist3=40
                #To do: use gpio setting mode
                GPIO.setmode(GPIO.BOARD)
                
                GPIO.setup(self.ArduEna_Base, GPIO.IN)
                GPIO.setup(self.ArduEna_LowArm, GPIO.IN)
                GPIO.setup(self.ArduEna_UpArm, GPIO.IN)
                GPIO.setup(self.ArduEna_Wrist1, GPIO.IN)
                GPIO.setup(self.ArduEna_Wrist2, GPIO.IN)
                GPIO.setup(self.ArduEna_Wrist3, GPIO.IN)
               
                print "Serial initialization... "
                self.port=serial.Serial(PortNum,baudrate,timeout=3)
                time.sleep(3)
                
                print "done. "

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
                #print "DetectWrist2ENA: ",GPIO.input(self.ArduEna_Wrist2)
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
                    
        def CloseSerial(self):
                self.port.close()

if __name__=='__main__':
        SerialSendToArduino=rpiControllArduinos()
        print 'sending data'
        
        

        
        SerialSendToArduino.MoveSteps('-2000a')
        SerialSendToArduino.MoveSteps('-2000b')
        SerialSendToArduino.MoveSteps('-2000c')
        SerialSendToArduino.MoveSteps('-2000c')
        SerialSendToArduino.MoveSteps('-2000d')
        SerialSendToArduino.MoveSteps('-2000e')
        SerialSendToArduino.MoveSteps('-2000f')
        while SerialSendToArduino.DetecAllENA()==0:
            time.sleep(0.01)
        
        SerialSendToArduino.MoveSteps('2000a')
        SerialSendToArduino.MoveSteps('2000b')
        SerialSendToArduino.MoveSteps('2000c')
        SerialSendToArduino.MoveSteps('2000c')
        SerialSendToArduino.MoveSteps('2000d')
        SerialSendToArduino.MoveSteps('2000e')
        SerialSendToArduino.MoveSteps('2000f')    
        
        SerialSendToArduino.DetecAllENA()
        #SerialSendToArduino.CloseSerial()
