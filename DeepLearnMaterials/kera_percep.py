from keras.models import Sequential
from keras.layers import Dense, Dropout, Activation
from keras.optimizers import SGD
import numpy as np

model = Sequential()
# Dense(64) is a fully-connected layer with 64 hidden units.
# in the first layer, you must specify the expected input data shape:
# here, 20-dimensional vectors.

data_dim=2
timesteps = 8
nb_classes = 10


x_train = np.random.random((2,data_dim))
#x_train = []
x_train=[[0, 0],[0, 1],[1, 0],[1, 1]]

y_train=[[0.0],[1],[1],[1]]

# generate dummy validation data
x_val = np.random.random((1, data_dim))
y_val = np.random.random((1, data_dim))


model.add(Dense(128, input_dim=2, init='uniform'))
model.add(Activation('linear'))
model.add(Dense(128, init='uniform'))
model.add(Activation('sigmoid'))
model.add(Dense(128, init='uniform'))
model.add(Activation('sigmoid'))

model.add(Dense(1, init='uniform'))
model.add(Activation('sigmoid'))

sgd = SGD(lr=0.01)
model.compile(loss='mse',
              optimizer=sgd,
              metrics=['accuracy'])

model.fit(x_train, y_train,
          nb_epoch=100,
          batch_size=10)
#score = model.evaluate(x_val, y_val, batch_size=16)
proba = model.predict_proba(x_train)
print proba
