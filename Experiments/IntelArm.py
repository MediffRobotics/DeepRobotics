import cv2
import numpy as np
from BrainDQN_Nature import BrainDQN
import arm

def preprocess(observation):
    observation = cv2.cvtColor(cv2.resize(observation, (80,80)), cv2.COLOR_BGR2GRAY)
    ret, observation = cv2.threshold(observation, 1, 255, cv2.THRESH_BINARY)
    return np.reshape(observation, (80,80,1))

def moveArm():
    actions = 3
    brain = BrainDQN(actions)
    arm_state = arm.ArmState()
    action10 = np.array([0,0,0])
    action20 = np.array([0,0,0])
    action30 = np.array([0,0,0])
    action40 = np.array([0,0,0])
    action50 = np.array([0,0,0])
    action60 = np.array([0,0,0])
    observation0, reward = arm_state.angle_state(action10,action20,action30,
                                            action40,action50,action60)
    observation0 = preprocess(observation0)
    brain.setInitState(observation0)

    while 1 != 0:
        action = brain.getAction()
        nextObservation,reward,terminal = arm_state.angle_state(action10
                            ,action20,action30,action40,action50,action60)
        #nextObservation = preprocess(nextObservation)
        #brain.setPerception(nextObservation,action,reward,terminal)
        cv2.imshow('control', 0)
        if cv2.waitKey(1) & 0xFF == 27:
            break

if __name__ == '__main__':
    moveArm()
