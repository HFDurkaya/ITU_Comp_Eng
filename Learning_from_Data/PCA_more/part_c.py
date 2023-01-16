import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
import math
import random
import seaborn as sb
from sklearn.model_selection import KFold

def PCA(x, k):
    x_mean = x - np.mean(x, axis=0)

    x_cov = np.cov(x_mean, rowvar = False)

    eigen_values, eigen_vectors = np.linalg.eigh(x_cov)

    index_sorted = np.argsort(eigen_values)[::-1]
    eigen_values_sorted = eigen_values[index_sorted]
    eigen_vectors_sorted = eigen_vectors[:,index_sorted]

    subset_eigen_vectors = eigen_vectors_sorted[:,0:k]

    reduced_X = np.dot(subset_eigen_vectors.transpose(), x_mean.transpose()).transpose()

    return reduced_X

url = "https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data"
data = pd.read_csv(url, names=['sepal length','sepal width','petal length','petal width','target'])

x = data.iloc[:,0:4]

target = data.iloc[:,4]

reduced_matrix = PCA(x,2)

df = pd.DataFrame(reduced_matrix, columns = ['1','2'])
df = pd.concat([df, pd.DataFrame(target)], axis = 1)

print(df)

plt.figure(figsize = (6,6))
sb.scatterplot(data = df, x = '1', y= '2', hue = 'target', s = 60, palette = 'icefire')
plt.show()