import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
import math
import random
from sklearn.model_selection import KFold

# Reading dataframes from .CSV files
# And converting dataframes from DataFrame type to numpy.ndarray type
# To delete the first index column, [:, 1:] has been added to the end
dataset_1 = pd.read_csv("train1.csv").to_numpy()[:, 1:]
dataset_2 = pd.read_csv("train2.csv").to_numpy()[:, 1:]


# Function that calculates and visualize covariance matrix
def covariance_matrix_plot(data, title, x_labels, y_labels, plot=True):
    # Calculating mean for each column
    num_cols = len(data[0])
    means = [0] * num_cols
    for i in range(num_cols):
        col_sum = 0
        for row in data:
            col_sum += float(row[i])
        means[i] = col_sum / len(data)

    # Calculating covariance matrix
    covariance_matrix = [[0] * num_cols for i in range(num_cols)]
    for i in range(num_cols):
        for j in range(num_cols):
            sum = 0
            for row in data:
                sum += (float(row[i]) - means[i]) * (float(row[j]) - means[j])
            covariance_matrix[i][j] = sum / (len(data) - 1)

    # Printing covariance matrix
    #for row in covariance_matrix:
    #   print(row)

    fig, ax = plt.subplots()
    heatmap = ax.pcolor(covariance_matrix)

    ax.set_title(title)

    ticks = [1 * i + 0.5 for i in range(len(x_labels))]
    ax.set_xticks(ticks)
    ax.set_yticks(ticks)
    ax.set_xticklabels(x_labels)
    ax.set_yticklabels(y_labels)

    fig.colorbar(heatmap)

    if plot:
        plt.show()

    return covariance_matrix


# Function that plots data distribution of features
def histogram_plot(data_class0, data_class1, dataset_name):


    plt.hist(data_class0[:, 0], bins = 25, alpha=0.5, label='Class 0', color='red')
    plt.hist(data_class1[:, 0], bins = 25, alpha=0.5, label='Class 1', color='blue')
    plt.legend(loc='upper right')
    plt.title("Histogram Plot of Data Distribution of " + dataset_name + " - Feature 0")

    # Showing plot
    plt.show()

    plt.hist(data_class0[:, 1], bins = 25, alpha=0.5, label='Class 0', color='red')
    plt.hist(data_class1[:, 1], bins = 25, alpha=0.5, label='Class 1', color='blue')
    plt.legend(loc='upper right')
    plt.title("Histogram Plot of Data Distribution of " + dataset_name + " - Feature 1")

    # Showing plot
    plt.show()


# Function that scatter plots of classes
def scatter_plot(data_class0, data_class1, dataset_name):
    # Creating scatter plot
    plt.scatter(data_class0[:, 0], data_class0[:, 1], alpha=0.5, label='Class 0', color='red')
    plt.scatter(data_class1[:, 0], data_class1[:, 1], alpha=0.5, label='Class 1', color='blue')

    # Adding labels and title
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title("Scatter Plot of x and y of " + dataset_name)
    plt.legend(loc='upper right')

    # Showing plot
    plt.show()


dataset1_class0 = dataset_1[dataset_1[:, 2] == 0, :2]
dataset1_class1 = dataset_1[dataset_1[:, 2] == 1, :2]

dataset2_class0 = dataset_2[dataset_2[:, 2] == 0, :2]
dataset2_class1 = dataset_2[dataset_2[:, 2] == 1, :2]

dataset1_covariance_class0 = covariance_matrix_plot(dataset1_class0, "Dataset_1 - Class 0 ", ['x1', 'x2'], ['x1', 'x2'])
dataset1_covariance_class1 = covariance_matrix_plot(dataset1_class1, "Dataset_1 - Class 1 ", ['x1', 'x2'], ['x1', 'x2'])

dataset2_covariance_class0 = covariance_matrix_plot(dataset2_class0, "Dataset_2 - Class 0 ", ['x1', 'x2'], ['x1', 'x2'])
dataset2_covariance_class1 = covariance_matrix_plot(dataset2_class1, "Dataset_2 - Class 1 ", ['x1', 'x2'], ['x1', 'x2'])

histogram_plot(dataset1_class0, dataset1_class1, "Dataset 1")
histogram_plot(dataset2_class0, dataset2_class1, "Dataset 2")

scatter_plot(dataset1_class0, dataset1_class1, "Dataset 1")
scatter_plot(dataset2_class0, dataset2_class1, "Dataset 2")


def getMean(data_class):
    num = 0.0
    
    sum_x1 = 0
    sum_x2 = 0

    for i in data_class[:,0]:
        sum_x1 = sum_x1 + i
        num = num + 1
    mean_x1 = (sum_x1/num) 

    for i in data_class[:,1]:
        sum_x2 = sum_x2 + i
    mean_x2 = (sum_x2/num)

    return np.array([mean_x1, mean_x2])

def sqr_mah_dist(x, mean, covariance):
    
    x = x - mean
    return np.transpose(x) @ np.linalg.inv(covariance) @ x

def bayes_train(cov0, cov1, mean0, mean1, c0_prob, c1_prob):
    
    if(np.array_equal(cov0, cov1)):

        g0 = lambda x: (-1/2) * sqr_mah_dist(x,mean0, cov0) + c0_prob
        g1 = lambda x: (-1/2) * sqr_mah_dist(x, mean1, cov0) + c1_prob
    
    else:
        g0 = lambda x: (-1/2) * sqr_mah_dist(x, mean0, cov0) - (1/2) * np.log(np.linalg.det(cov0)) + c0_prob
        g1 = lambda x: (-1/2) * sqr_mah_dist(x, mean1, cov1) - (1/2) * np.log(np.linalg.det(cov1)) + c1_prob
    return g0, g1


dataset1_mean0 = getMean(dataset1_class0)
dataset1_mean1 = getMean(dataset1_class1)
dataset2_mean0 = getMean(dataset2_class0)
dataset2_mean1 = getMean(dataset2_class1)

probability_dataset1_class0 = np.log(len(dataset1_class0)/len(dataset_1))
probability_dataset1_class1 = np.log(len(dataset1_class1)/len(dataset_1))
probability_dataset2_class0 = np.log(len(dataset2_class0)/len(dataset_2))
probability_dataset2_class1 = np.log(len(dataset2_class1)/len(dataset_2))

g0_dataset1, g1_dataset1 = bayes_train(dataset1_covariance_class0, dataset1_covariance_class1, dataset1_mean0,
                            dataset1_mean1,probability_dataset1_class0, probability_dataset1_class1)
g0_dataset2, g1_dataset2 = bayes_train(dataset2_covariance_class0, dataset2_covariance_class1, dataset2_mean0,
                            dataset2_mean1,probability_dataset2_class0, probability_dataset1_class1)


def checkResult(x, g0, g1):
    return 0 if g0(x) > g1(x) else 1 

def bayesTest(g0, g1 ,test):

    error = 0
    accuracy = 0
    prediction = []
    var = None
    i = 0

    for row in test:

        if(g0(row[:2]) > g1(row[:2])):
            var = 0
        else:
            var = 1
        if(var != row[2]):
            prediction.append(1-row[2])
            error = error + 1

        else:
            prediction.append(row[2])
            accuracy = accuracy + 1
        i = i + 1
    error = (error/(len(test))) * 100
    accuracy = (accuracy / (len(test))) * 100
    return error, accuracy

test_1 = pd.read_csv("test1.csv").to_numpy()[:, 1:]
test_2 = pd.read_csv("test2.csv").to_numpy()[:, 1:]

print("Error, Accuracy for dataset 1 (percentage): ", bayesTest(g0_dataset1, g1_dataset1, test_1))
print("Error, Accuracy for dataset 2 (percentage): ", bayesTest(g0_dataset2, g1_dataset2, test_2))


print("Dataset 1 class 0 --> x1 and x2: ",dataset1_mean0)
print("Dataset 1 class 1 --> x1 and x2: ",dataset1_mean1)
print("Dataset 2 class 0 --> x1 and x2: ",dataset2_mean0)
print("Dataset 2 class 1 --> x1 and x2: ",dataset2_mean1)

print("Dataset 1 class 0 Covariance Matrix:",dataset1_covariance_class0)
print("Dataset 1 class 1 Covariance Matrix:",dataset1_covariance_class1)
print("Dataset 2 class 0 Covariance Matrix:",dataset2_covariance_class0)
print("Dataset 2 class 1 Covariance Matrix:",dataset2_covariance_class1)

