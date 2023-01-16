import csv
import matplotlib.pyplot as plt
import numpy


# read data from CSV file
data1 = []
with open('train1.csv') as csvfile:
    csvreader = csv.reader(csvfile)
    for row in csvreader:
        data1.append(row[1:])

data2 = []
with open('train2.csv') as csvfile:
    csvreader = csv.reader(csvfile)
    for row in csvreader:
        data2.append(row[1:])

def cov_matrix(data):
    # calculate mean for each column
    num_cols = len(data[0])
    means = [0] * num_cols
    for i in range(num_cols):
        col_sum = 0
        for row in data:
            col_sum += float(row[i])
        means[i] = col_sum / len(data)

    # calculate covariance matrix
    covariance_matrix = [[0] * num_cols for i in range(num_cols)]
    for i in range(num_cols):
        for j in range(num_cols):
            sum = 0
            for row in data:
                sum += (float(row[i]) - means[i]) * (float(row[j]) - means[j])
            covariance_matrix[i][j] = sum / (len(data) - 1)

    # print covariance matrix
    for row in covariance_matrix:
        print(row)

    print(covariance_matrix)
    fig, ax = plt.subplots()

    heatmap = ax.pcolor(covariance_matrix)

    fig.colorbar(heatmap)

    plt.show()
    return covariance_matrix

def figures(data):
    # extract x and y data from CSV file
    x_data = [float(row[0]) for row in data]
    y_data = [float(row[1]) for row in data]

    # create scatter plot
    plt.scatter(x_data, y_data)

    # add labels and title
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Scatter Plot of x and y')

    # show plot
    plt.show()

def histograms(data1, data2):
    
    
    x1_data = [float(row[0]) for row in data1]
    x2_data = [float(row[0]) for row in data2]

    y1_data = [float(row[0]) for row in data1]
    y2_data = [float(row[0]) for row in data2]

    bins = numpy.linspace(-5, 5, 50)

    plt.hist(x1_data, bins, alpha=0.5, label='x1',color = 'red')
    plt.hist(x2_data, bins, alpha=0.5, label='x2', color = 'blue')
    plt.legend(loc='upper right')

    bins1 = numpy.linspace(-5, 5, 50)

    plt.hist(y1_data, bins1, alpha=0.5, label='y1',color = 'black')
    plt.hist(y2_data, bins1, alpha=0.5, label='y2', color = 'red')
    plt.legend(loc='lower right')

    plt.show()
    plt.show()



cov_matrix(data1)
figures(data1)
cov_matrix(data2)
figures(data2)
histograms(data1,data2)
mean_vectors(data1)
mean_vectors(data2)