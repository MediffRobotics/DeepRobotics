import cv2
from TakePicture import CCamera
from tcpClient import  clientSocketControllArm
import time

class ArmState:
    def __init__(self):
        self.angle1 = 0.0
        self.angle2 = 0.0
        self.angle3 = 0.0
        self.angle4 = 0.0
        self.angle5 = 0.0
        self.angle6 = 0.0
        self.camera = CCamera()
        self.camera.setDaemon(True)
        self.camera.start()
        time.sleep(1)
        self.sockClient=clientSocketControllArm()

    def angle_state(self, input_action1):
        reward = 0
        terminal = False

        if sum(input_action1) != 1:
            raise ValueError('Invalid input actions!')

            #Angle of engine 1
        if input_action1[0] == 1:
            self.angle1 = -1
        elif input_action1[1] == 1:
            self.angle1 = 0
        else:
            self.angle1 = 1


        #print self.angle1
        reward=self.sockClient.ClientSendAngle(self.angle1)

        time.sleep(0.5)
        observation = self.camera.frame
        return observation, reward, terminal
