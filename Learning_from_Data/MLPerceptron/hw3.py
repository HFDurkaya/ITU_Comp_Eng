import numpy as np
import matplotlib.pyplot as plt

training_df = np.genfromtxt('optdigits.tra', delimiter=",")     #loading the data using numpy to use it as numpy array
X_training = training_df[:, 0:63]
y_training = training_df[:, 64]

testing_df = np.genfromtxt('optdigits.tes', delimiter=",")
X_testing = testing_df[:, 0:63]
y_testing = testing_df[:, 64]

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def derivative_sigmoid(x):
    return sigmoid(x) * (1 - sigmoid(x))


size = training_df.shape

#Numvber of inputs
train = size[0]                
#column count
C = size[1]
#last column is not a featyre , it's the label
number_of_features = C - 1
#learning rate
laerning_rate = 0.99
weight_decay = 1

#implementation specific variables to use 

first_hidden_layer = 2
second_hidden_layer = 64
class_count = 10

# weights are initalized as randoms

weight_1 = -0.01 + 0.02 * np.random.rand(first_hidden_layer, number_of_features)
weight_2 = -0.01 + 0.02 * np.random.rand(second_hidden_layer, first_hidden_layer)
weight_3 = -0.01 + 0.02 * np.random.rand(class_count, second_hidden_layer)

#biases are initalized as randoms

bias_1 = -0.01 + 0.02 * np.random.rand(first_hidden_layer, 1)
bias_2 = -0.01 + 0.02 * np.random.rand(second_hidden_layer, 1)
bias_3 = -0.01 + 0.02 * np.random.rand(class_count, 1)

#created an identity matrix in size 10x10

classes = np.eye(10, 10)

r = training_df[:, 64] 


dw3 = np.zeros([class_count, second_hidden_layer])
dw2 = np.zeros([second_hidden_layer, first_hidden_layer])
dw1 = np.zeros([first_hidden_layer, number_of_features])

db3 = np.zeros([class_count, 1])
db2 = np.zeros([second_hidden_layer, 1])
db1 = np.zeros([first_hidden_layer, 1])

for i in range(1):
    for new_input in range(train):
        x = np.transpose(np.array([training_df[new_input, :64]]))
        a_1 = x

        z_2 = weight_1 @ a_1 + bias_1
        print("Z_2 ", z_2)
        a_2 = sigmoid(z_2)
        z_3 = weight_2 @ a_2 + bias_2
        a_3 = sigmoid(z_3)
        z_4 = weight_3 @ a_3 + bias_3
        a_4 = sigmoid(z_4)

        y = np.array([classes[:, int(r[new_input])]]).T
        # print("y ", y.shape)
        # print("A4 ", a_4.shape)
        # print(a_4)
        # print("z4 ", z_4.shape)
        # print(z_4)
        d_4 = -(y - a_4) * derivative_sigmoid(z_4)
        d_3 = (np.transpose(weight_3) @ d_4) * derivative_sigmoid(z_3)
        d_2 = (np.transpose(weight_2) @ d_3) * derivative_sigmoid(z_2)

        pdw3 = d_4 @ np.transpose(a_3)
        pdw2 = d_3 @ np.transpose(a_2)
        pdw1 = d_2 @ np.transpose(a_1)

        pdb3 = d_4
        pdb2 = d_3
        pdb1 = d_2

        dw3 += pdw3
        dw2 += pdw2
        dw1 += pdw1

        db3 += pdb3
        db2 += pdb2
        db1 += pdb1

        weight_3 -= (laerning_rate * (dw3 / train)) + weight_decay * weight_3
        weight_2 -= (laerning_rate * (dw2 / train)) + weight_decay * weight_2
        weight_1 -= (laerning_rate * (dw1 / train)) + weight_decay * weight_1

        bias_3 -= (laerning_rate * (db3 / train))
        bias_2 -= (laerning_rate * (db2 / train))
        bias_1 -= (laerning_rate * (db1 / train))


correct = 0

hidden_1 = []
hidden_2 = []
predictions = []


for examine in range(testing_df.shape[0]):
    first = weight_1 @ np.transpose(np.array([testing_df[examine, :64]])) + bias_1
    first = 1 / (1 + np.exp(-first))

    hidden_1.append(first[0])
    hidden_2.append(first[1])

    second = weight_2 @ first + bias_2
    second = 1 / (1 + np.exp(-second))

    third = weight_3 @ second + bias_3
    third = 1 / (1 + np.exp(-third))

    index = np.argmax(third)
    predictions.append(index)

    real_label = testing_df[examine, 64]
    predicted_label = index - 1

    if real_label == predicted_label:
        correct += 1

#print(hidden_1)
plt.scatter(hidden_1, hidden_2, c=predictions, cmap='viridis')
plt.xlabel('Hidden unit 1')
plt.ylabel('Hidden unit 2')
plt.colorbar().set_label('Predicted class')
plt.show()

accuracy = correct/testing_df.shape[0]
print("Accuracy", accuracy)
