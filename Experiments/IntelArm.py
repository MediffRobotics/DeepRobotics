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
    action10 = np.array([0,1,0]) 
    observation0, reward = arm_state.angle_state(action10)
    observation0 = cv2.cvtColor(cv2.resize(observation0, (80,80)), cv2.COLOR_BGR2GRAY)
    ret, observation0 = cv2.threshold(observation0, 1, 255, cv2.THRESH_BINARY)
    brain.setInitState(observation0)

    while 1 != 0:
        action = brain.getAction()
        print action
        nextObservation,reward = arm_state.angle_state(action)
        print reward
        nextObservation = preprocess(nextObservation)
        brain.setPerception(nextObservation,action,reward)
        cv2.imshow('Observation', nextObservation)
        if cv2.waitKey(1) & 0xFF == 27:
            break

if __name__ == '__main__':
    moveArm()
