from micromlgen import port
from sklearn.svm import SVC
from sklearn.datasets import load_iris
from model_selection import model_selection2



clf = SVC(C = 0.1,kernel='linear',gamma = 0.001)
# X, y = load_iris(return_X_y=True)
# clf.fit(X,y)
print(port(clf))

