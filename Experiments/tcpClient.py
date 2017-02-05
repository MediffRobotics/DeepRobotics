import socket
import SockCommun_Brain_Rpi as sbr
import sys
import time
class clientSocketControllArm:
    def __init__(self):
        self.converter = sbr.BrainCommuViaSock()

    def ClientSendAngle(self,angle1):
        host = '192.168.0.16'
        port = 3000

        s = socket.socket()
        s.connect((host, port))

        steps1 = self.converter.UpArm_Angles2Steps(angle1)
        print 'steps val: ' + str(steps1)
        s.send(str(steps1) + 'B')
        data = s.recv(1024)
        if(angle1<=-1):
            data=1;
        else: 
            data=0;
        print 'Recieved from server: ' + str(data)

	
        s.close()
        #print "data: "
        data=int(str(data))
        #print data
        #sys.exit()
        return data

if __name__ == '__main__':
    sockClient=clientSocketControllArm()
    sockClient.ClientSendAngle(-2)
    time.sleep(2)
    sockClient.ClientSendAngle(0)
    time.sleep(2)
    sockClient.ClientSendAngle(2)
    time.sleep(2)
    sockClient.ClientSendAngle(0)
    time.sleep(2)
