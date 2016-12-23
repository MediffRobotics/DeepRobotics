
import time
import sys
sys.path.append("../rpiControllsArduinos/")
sys.path.append("../rpiSocketCommu/")
import SerialGpioControllArduinos 
import rpiSocketCommu_server


if __name__=='__main__':
	
    socketCommObj=rpiSocketCommu_server.SocketCommu()
    SerialSendToArduino=SerialGpioControllArduinos.rpiControllArduinos()
	
    strMoveCommand='0'
    while 1:
        strMoveCommand=socketCommObj.AcceptSock()
        #sleep(1)
        print 'received: ', strMoveCommand
        SerialSendToArduino.MoveSteps(strMoveCommand)

    SerialSendToArduino.CloseSerial()
    socketCommObj.CloseSocket()
