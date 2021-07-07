import numpy as np
from glob import glob
from os.path import basename
import pandas as pd
from scipy.sparse import data
from sklearn.preprocessing import LabelEncoder, normalize
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import mean_squared_error


def load_features(folder):
    dataset = np.array([])
    label = np.array([])
    count = (len(glob('%s/*.csv' % folder)))
    for class_idx, filename in enumerate(glob('%s/*.csv' % folder)):
        name = basename(filename)[:-6]
        sample = pd.read_csv(filename, ',')
        sample = np.array(sample).reshape(1, len(sample))[0]
        dataset = np.append(dataset, sample)
        label = np.append(label, name)
    dataset = dataset.reshape(count, len(sample))
    return dataset, label


folder = 'dataset'
dataset, label = load_features(folder)
le = LabelEncoder()
int_label = (le.fit_transform(label))
X, y = dataset, int_label

# Normalisation
X_mean = X.mean(axis=0)
X = np.round((X-X_mean), 2)

# pca = PCA(n_components=2)
# pca.fit(X)
# X = pca.transform(X)

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.33, random_state=42, shuffle=True)


# lists with the parameters for the classifier SVM
clf = SVC(C=1, kernel='rbf', gamma=1)
clf.fit(X_train,y_train)
pred = clf.predict(X_test)

rmse = np.sqrt(mean_squared_error(y_test, pred))
print("RMSE: %f" % (rmse))

# h = 0.1
# x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
# y_min, y_max = X[:, 0].min() - 1, X[:, 0].max() + 1
# xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
#                      np.arange(y_min, y_max, h))

# z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
# z = z.reshape(xx.shape)
# plt.contourf(xx, yy, z)
# plt.scatter(X[:, 0], X[:, 1], c=y, alpha=0.5,
#             label="Luck")

# plt.show()
