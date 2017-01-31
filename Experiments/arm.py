import cv2
from TakePicture import CCamera
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
    def angle_state(self, input_action1):
        reward = 0

        if sum(input_action1) != 1:
            raise ValueError('Invalid input actions!')
            '''
            if sum(input_action1) != 1:
                raise ValueError('Invalid input actions!')
            if sum(input_action1) != 1:
                raise ValueError('Invalid input actions!')
            if sum(input_action1) != 1:
                raise ValueError('Invalid input actions!')
            if sum(input_action1) != 1:
                raise ValueError('Invalid input actions!')
            if sum(input_action1) != 1:
                raise ValueError('Invalid input actions!')
            '''
            #Angle of engine 1
        if input_action1[0] == 1:
            self.angle1 -= 1
        elif input_action1[1] == 1:
            pass
        else:
            self.angle1 += 1
            '''
            #Angle of engine 2
            if input_action2[0] == 1:
                self.angle2 -= 1
            elif input_action2[1] == 1:
                pass
            else:
                self.angle2 += 1

            #Angle of engine 3
            if input_action3[0] == 1:
                self.angle3 -= 1
            elif input_action3[1] == 1:
                pass
            else:
                self.angle3 += 1

            #Angle of engine 4
            if input_action4[0] == 1:
                self.angle4 -= 1
            elif input_action4[1] == 1:
                pass
            else:
                self.angle4 += 1

            #Angle of engine 5
            if input_action5[0] == 1:
                self.angle5 -= 1
            elif input_action5[1] == 1:
                pass
            else:
                self.angle5 += 1

            #Angle of engine 6
            if input_action6[0] == 1:
                self.angle6 -= 1
            elif input_action6[1] == 1:
                pass
            else:
                self.angle6 += 1
            '''

        observation = self.camera.frame

        return observation, reward
