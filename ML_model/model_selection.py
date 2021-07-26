from micromlgen import port
from inspect import Parameter
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
from sklearn.model_selection import KFold


def load_features(folder):
    dataset = np.array([])
    label = np.array([])
    classmap = {}
    count = (len(glob('%s/*.csv' % folder)))
    for class_idx, filename in enumerate(glob('%s/*.csv' % folder)):
        name = basename(filename)[:-7]
        classmap[class_idx] = name
        sample = pd.read_csv(filename, ',')
        sample = np.array(sample).reshape(1, len(sample))[0]
        dataset = np.append(dataset, sample)
        label = np.append(label, name)
    dataset = dataset.reshape(count, len(sample))
    return dataset, label, classmap


def classifier(classifier, dataset, label, **kwargs):

    le = LabelEncoder()
    int_label = (le.fit_transform(label))
    X, y = dataset, int_label

    cv = KFold(n_splits=5, shuffle=True, random_state=42)

    score_array = np.array([])
    rmse_array = np.array([])

    for _ in range(10):
        for train_index, test_index in cv.split(X):
            train_data = X[train_index]
            train_label = y[train_index]
            test_data = X[test_index]
            test_label = y[test_index]

            # # lists with the parameters for the classifier SVM
            clf = classifier(**kwargs)
            clf.fit(train_data, train_label)
            pred = clf.predict(test_data)
            score = clf.score(test_data, test_label)
            rmse = np.sqrt(mean_squared_error(test_label, pred))
            score_array = np.append(score_array, score)
            rmse_array = np.append(rmse_array, rmse)

    score = np.mean(score_array)
    rmse = np.mean(rmse_array)

    print("RMSE: %f" % (rmse))
    print("Score: %f" % (score))
    classifier_performance = {
        'Name': classifier.__name__, **kwargs, 'Score': round((score*100), 2)}
    return clf, classifier_performance

    # c_code = port(clf, classmap=classmap)

    # with open("model_RandomForest.h", "w") as text_file:
    #     text_file.write(c_code)


def model_selection(folder_address):

    folder = folder_address
    dataset, label, classmap = load_features(folder)

    classifiers = [SVC]#, RandomForestClassifier, DecisionTreeClassifier]

    # lists with the parameters for the classifier SVM
    c_values = [0.1, 1, 10, 100, 1000, 10000]
    kernels = ['linear', 'sigmoid', 'poly']
    gamma_values = [1, 0.1, 0.01, 0.001, 0.0001]
    degree_values = [2, 3, 4, 5, 6]
    coef0_values = [0, 0.25, 0.5, 0.75, 1]

    # lists with the parameters for the classifier Random forest
    n_estimators_ = [10, 40, 80, 100]
    max_depth_ = [2, 8, 16, 20]

    performances = pd.DataFrame()

    for clf in classifiers:
        if clf == SVC:
            for C in c_values:
                for kernel in kernels:
                    if kernel == 'rbf' or kernel == 'poly' or kernel == 'sigmoid':
                        for gamma in gamma_values:
                            if kernel == 'poly' or kernel == 'sigmoid':
                                for coef0 in coef0_values:
                                    if kernel == 'poly':
                                        for degree in degree_values:
                                            parameters = {
                                                'C': C, 'kernel': kernel, 'gamma': gamma, 'degree': degree, 'coef0': coef0}
                                            _, performance = classifier(
                                                clf, dataset, label, **parameters)
                                            performances = performances.append(
                                                (performance), ignore_index=True)
                                            print(performance)
                                    else:
                                        parameters = {
                                            'C': C, 'kernel': kernel, 'gamma': gamma, 'coef0': coef0}
                                        _, performance = classifier(
                                            clf, dataset, label, **parameters)
                                        performances = performances.append(
                                            (performance), ignore_index=True)
                                        print(performance)
                            else:
                                parameters = {
                                    'C': C, 'kernel': kernel, 'gamma': gamma}
                                _, performance = classifier(
                                    clf, dataset, label, **parameters)
                                performances = performances.append(
                                    (performance), ignore_index=True)
                                print(performance)
                    else:
                        parameters = {'C': C, 'kernel': kernel}
                        _, performance = classifier(
                            clf, dataset, label, **parameters)
                        performances = performances.append(
                            (performance), ignore_index=True)
                        print(performance)

        elif clf == RandomForestClassifier:
            for n_estimator in n_estimators_:
                for max_depth in max_depth_:
                    parameters = {'n_estimators': n_estimator,
                                  'max_depth': max_depth}
                    _, performance = classifier(
                        clf, dataset, label, **parameters)
                    performances = performances.append(
                        (performance), ignore_index=True)

                    print(performance)
        else:
            _, performance = classifier(clf, dataset, label)
            performances = performances.append(
                (performance), ignore_index=True)

            print(performance)

    Short_list = performances.sort_values(
        by=['Score'], ascending=False).iloc[:10, :]
    pd.DataFrame(Short_list).to_csv("classifier_shortlist.csv", index=False)


# def model_selection2(X, y):

#     dataset, label = X, y

#     classifiers = [MLPClassifier]

#     # lists with the parameters for the classifier SVM
#     activation = ['identity', 'logistic', 'tanh', 'relu']
#     solver = ['lbfgs', 'sgd', 'adam']
#     alpha = [1, 0.1, 0.01, 0.001, 0.0001]
#     learning_rate = ['constant', 'invscaling', 'adaptive']

#     # # lists with the parameters for the classifier Random forest
#     # n_estimators_ = [10, 40, 80, 100]
#     # max_depth_ = [2, 8, 16, 20]

#     performances = pd.DataFrame()
#     clf = MLPClassifier
#     for A in activation:
#         for S in solver:
#                 for al in alpha:
#                         for l in learning_rate:
#                                     parameters = {
#                                         'activation': A, 'solver': S, 'alpha': al, 'learning_rate': l,'max_iter':10000}
#                                     _, performance = classifier(
#                                         clf, dataset, label, **parameters)
#                                     performances = performances.append(
#                                         (performance), ignore_index=True)
#                                     print(performance)



if __name__ == '__main__':

    import six
    import sys
    sys.modules['sklearn.externals.six'] = six
    from skbayes.rvm_ard_models import RVC
    import warnings
    warnings.filterwarnings("ignore")

    folder = 'dataset'
    dataset, label,classmap = load_features(folder)
    le = LabelEncoder()
    int_label = (le.fit_transform(label))


    X, x, Y, y = train_test_split(
        dataset, int_label, test_size=0.33, random_state=42)

    clf = RVC(kernel='rbf')
    # clf = SVC(C=1, kernel='linear', gamma=0.1)
    clf.fit(X, Y)

    print(clf.score(x,y))

    prdction = [X[7]]
    print(prdction)

    print(clf.predict(prdction))

    c_code = port(clf)
    with open('model.h', "w") as text_file:
        text_file.write(c_code)



    
