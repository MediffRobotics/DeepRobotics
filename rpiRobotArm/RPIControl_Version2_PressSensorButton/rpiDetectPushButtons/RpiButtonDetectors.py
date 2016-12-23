import RPi.GPIO as GPIO
import time
import serial
import threading
import random

class RpiRobotArmButtons(threading.Thread):
        
        def __init__(self):                
            
            
            
            self.FlagPress_TeachingButton=0
            self.FlagPress_InsertMovementButton=0
            self.FlagPress_PlayResetButton=0
            
            self.TeachingButton=38
            self.InsertMovementButton=36
            self.PlayResetButton=32

            
            #To do: use gpio setting mode
            GPIO.setmode(GPIO.BOARD)
            
            GPIO.setup(self.TeachingButton, GPIO.IN)
            GPIO.setup(self.InsertMovementButton, GPIO.IN)       
            GPIO.setup(self.PlayResetButton, GPIO.IN)
                          
            threading.Thread.__init__(self)
            
            print "done for buttons "
        def run(self):
            
            while 1:
               self.DetectTeachingButton() 
               self.DetectInsertMovementButton() 
               self.DetectPlayResetButton()
                     
        def DetectTeachingButton(self):
            
            in_value= GPIO.input(self.TeachingButton)
            time.sleep(0.2)
            if in_value ==False:
               #print "Pressed teaching"
               self.FlagPress_TeachingButton=1
               
               while in_value == False:
                  in_value = GPIO.input(self.TeachingButton)
                  #time.sleep(0.1)
                      
        def DetectInsertMovementButton(self):
            global mutex
            
            in_value= GPIO.input(self.InsertMovementButton)
            time.sleep(0.2)
            if in_value ==False:
               
               #print "Pressed Insert new Movement"     
               self.FlagPress_InsertMovementButton=1
               while in_value == False:
                  in_value = GPIO.input(self.InsertMovementButton)
                  
                 
                  
        def DetectPlayResetButton(self):
           
            in_value= GPIO.input(self.PlayResetButton)
            time.sleep(0.2)
            if in_value ==False:
               #print "Pressed Play/ResetButton"
               self.FlagPress_PlayResetButton=1
               
               while in_value == False:
                  in_value = GPIO.input(self.PlayResetButton)
                  #time.sleep(0.1)
                  
if __name__=='__main__':
    Rpibutton=RpiRobotArmButtons()
    Rpibutton.setDaemon(True)
    Rpibutton.start()
    time.sleep(10)
    #Rpibutton.DetectTeachingButton()
