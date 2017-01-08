# -*- coding: utf-8 -*-
"""
Simple Example to train logical operators
"""

from __future__ import absolute_import, division, print_function

import tensorflow as tf
import tflearn

'''
Going further: Graph combination with multiple optimizers
Create a XOR operator using product of NAND and OR operators
'''
# Data
X = [[0., 0.], [0., 1.], [1., 0.], [1., 1.]]
Y_nand = [[1.], [1.], [1.], [0.]]
Y_or = [[0.], [1.], [1.], [1.]]

# Graph definition
with tf.Graph().as_default():
    # Building a network with 2 optimizers
    g = tflearn.input_data(shape=[None, 2])

    # Nand operator definition
    g_nand = tflearn.fully_connected(g, 32, activation='linear')
    g_nand = tflearn.fully_connected(g_nand, 32, activation='linear')
    g_nand = tflearn.fully_connected(g_nand, 1, activation='sigmoid')
    g_nand = tflearn.regression(g_nand, optimizer='sgd',
                                learning_rate=2.,
                                loss='binary_crossentropy')
    # Or operator definition
    g_or = tflearn.fully_connected(g, 32, activation='linear')
    g_or = tflearn.fully_connected(g_or, 30, activation='linear')
    g_or = tflearn.fully_connected(g_or, 1, activation='sigmoid')
    g_or = tflearn.regression(g_or, optimizer='sgd',
                              learning_rate=2.,
                              loss='binary_crossentropy')
    # XOR merging Nand and Or operators
    g_xor = tflearn.merge([g_nand, g_or], mode='elemwise_mul')

    # Training
    m = tflearn.DNN(g_xor,tensorboard_verbose=3)
    m.fit(X, [Y_nand, Y_or], n_epoch=400, snapshot_epoch=False)

    # Testing
    print("Testing XOR operator")
    print("0 xor 0:", m.predict([[0., 0.]]))
    print("0 xor 1:", m.predict([[0., 1.]]))
    print("1 xor 0:", m.predict([[1., 0.]]))
print("1 xor 1:", m.predict([[1., 1.]]))
