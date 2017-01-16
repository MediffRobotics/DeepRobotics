import socket
import SockCommun_Brain_Rpi as sbr

def Client():
    host = '192.168.0.16'
    port = 3000

    s = socket.socket()
    s.connect((host, port))

    converter = sbr.BrainCommuViaSock()

    angle_up = input('twister B -> ')
    angle_elbow = input('twister C -> ')
    quit = 'no'
    while quit != 'yes':
        steps1 = converter.UpArm_Angles2Steps(angle_up)
        steps2 = converter.Elbow_Angles2Steps(angle_elbow)
        s.send(str(steps1) + 'B')
        s.send(str(steps2) + 'C')
        #data = s.recv(1024)
        #print 'Recieved from server: ' + str(data)
        angle_up = input('twister B -> ')
        angle_elbow = input('twister C -> ')
        quit = raw_input('Disconnect to server? (yes/no) :')
    s.close()

if __name__ == '__main__':
    Client()
