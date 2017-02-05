import cv2
import numpy as np
from BrainDQN_Nature import BrainDQN
import arm

def preprocess(observation):
    observation = cv2.cvtColor(cv2.resize(observation, (80,80)), cv2.COLOR_BGR2GRAY)
    #ret, observation = cv2.threshold(observation, 1, 255, cv2.THRESH_TRUNC)
    cv2.adaptiveThreshold(observation,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,\
                                            cv2.THRESH_BINARY,11,2)
    return np.reshape(observation, (80,80,1))

def moveArm():
    actions = 3
    sum_reward = 0.0
    time_step = 0.0
    accuracy = 0.0
    brain = BrainDQN(actions)
    arm_state = arm.ArmState()
    action10 = np.array([0,1,0])

    observation0, reward, terminal = arm_state.angle_state(action10)
    observation0 = cv2.cvtColor(cv2.resize(observation0, (80,80)), cv2.COLOR_BGR2GRAY)
    #ret, observation0 = cv2.threshold(observation0, 1, 255, cv2.THRESH_BINARY)
    cv2.adaptiveThreshold(observation0,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,\
                                            cv2.THRESH_BINARY,11,2)
    brain.setInitState(observation0)

    while 1 != 0:
        action = brain.getAction()
        print "action:"
        print action
        nextObservation,reward, terminal = arm_state.angle_state(action)

        #print "reward: "
        #print reward
        sum_reward += reward
        time_step += 1
        accuracy = sum_reward / time_step
        print 'Accuracy: ' + str(accuracy)

        nextObservation = preprocess(nextObservation)
        brain.setPerception(nextObservation,action,reward, terminal)
        cv2.imshow('Observation', nextObservation)
        if cv2.waitKey(1) & 0xFF == 27:
            break

if __name__ == '__main__':
    moveArm()
