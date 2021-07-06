import numpy as np
from glob import glob
from os.path import basename
import pandas as pd
from scipy.sparse import data
from sklearn.preprocessing import LabelEncoder
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA

def load_features(folder):
    dataset = np.array([])
    label = np.array([])
    count = (len(glob('%s/*.csv' % folder)))
    for class_idx, filename in enumerate(glob('%s/*.csv' % folder)):
        name = basename(filename)[:-6]
        sample = pd.read_csv(filename,',')
        sample = np.array(sample).reshape(1,len(sample))[0]
        dataset = np.append(dataset,sample)
        label = np.append(label,name)
    dataset = dataset.reshape(count,len(sample))
    return dataset,label




folder= 'dataset'
dataset,label = load_features(folder)
le = LabelEncoder()
int_label = (le.fit_transform(label))
X,y = dataset,int_label
pca = PCA(n_components=2)
pca.fit(X)

X = pca.transform(X)



X_train, X_test, y_train, y_test = train_test_split(
X, y, test_size=0.33, random_state=42, shuffle=True)

clf = RandomForestClassifier(20, max_depth=10).fit(X_train, y_train)

# # print(clf.predict(X_test))
print(clf.score(X_test,y_test))