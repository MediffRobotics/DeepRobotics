import RPi.GPIO as GPIO
import time
import serial
import threading
import random

class RpiPowerRelay():
        
        def __init__(self):         
            self.RelayPin=26                                                    
            GPIO.setmode(GPIO.BOARD)            
            GPIO.setup(self.RelayPin, GPIO.OUT)
            GPIO.output(self.RelayPin,GPIO.HIGH)   
            print "done for relay "
        
        def SwitchOn(self):
            GPIO.output(self.RelayPin,GPIO.LOW)

            
        def SwitchOff(self):
            GPIO.output(self.RelayPin,GPIO.HIGH)   
        
if __name__=='__main__':
    PowerRelay=RpiPowerRelay()
    
    #while True:
    PowerRelay.SwitchOff()
    #    time.sleep(1)
    #    PowerRelay.SwitchOn()
    #    time.sleep(1)

    #Rpibutton.DetectTeachingButton()
