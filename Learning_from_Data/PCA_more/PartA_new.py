import numpy
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Reading dataframes from .CSV files
# And converting dataframes from DataFrame type to numpy.ndarray type
# To delete the first index column, [:, 1:] has been added to the end
dataset_1 = pd.read_csv("train1.csv").to_numpy()[:, 1:]
dataset_2 = pd.read_csv("train2.csv").to_numpy()[:, 1:]


# Function that calculates and visualize covariance matrix
def covariance_matrix_plot(data: numpy.ndarray, title, x_labels, y_labels, plot=True):
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
    for row in covariance_matrix:
        print(row)

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
def histogram_plot(data_class0: numpy.ndarray, data_class1: numpy.ndarray, dataset_name):
    bins = numpy.linspace(-5, 5, 50)

    plt.hist(data_class0[:, 0], bins, alpha=0.5, label='Class 0', color='red')
    plt.hist(data_class1[:, 0], bins, alpha=0.5, label='Class 1', color='blue')
    plt.legend(loc='upper right')
    plt.title("Histogram Plot of Data Distribution of " + dataset_name + " - Feature 0")

    # Showing plot
    plt.show()

    plt.hist(data_class0[:, 1], bins, alpha=0.5, label='Class 0', color='red')
    plt.hist(data_class1[:, 1], bins, alpha=0.5, label='Class 1', color='blue')
    plt.legend(loc='upper right')
    plt.title("Histogram Plot of Data Distribution of " + dataset_name + " - Feature 1")

    # Showing plot
    plt.show()


# Function that scatter plots of classes
def scatter_plot(data_class0: numpy.ndarray, data_class1: numpy.ndarray, dataset_name):
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

covariance_matrix_plot(dataset1_class0, "Dataset_1 - Class 0 ", ['x1', 'x2'], ['x1', 'x2'])
covariance_matrix_plot(dataset1_class1, "Dataset_1 - Class 1 ", ['x1', 'x2'], ['x1', 'x2'])

covariance_matrix_plot(dataset2_class0, "Dataset_2 - Class 0 ", ['x1', 'x2'], ['x1', 'x2'])
covariance_matrix_plot(dataset2_class1, "Dataset_2 - Class 1 ", ['x1', 'x2'], ['x1', 'x2'])

histogram_plot(dataset1_class0, dataset1_class1, "Dataset 1")
histogram_plot(dataset2_class0, dataset2_class1, "Dataset 2")

scatter_plot(dataset1_class0, dataset1_class1, "Dataset 1")
scatter_plot(dataset2_class0, dataset2_class1, "Dataset 2")
