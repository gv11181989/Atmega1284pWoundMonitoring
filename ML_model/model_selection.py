from micromlgen import port
from inspect import Parameter
import numpy as np
from glob import glob
from os.path import basename
from numpy.core.numeric import NaN
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
from skbayes.rvm_ard_models import RVC
from sklearn.metrics import confusion_matrix

import warnings
warnings.filterwarnings("ignore")


def load_features(folder):
    dataset = np.array([])
    label = np.array([])
    # classmap = {}
    count = (len(glob('%s/*.csv' % folder)))
    for filename in enumerate(glob('%s/*.csv' % folder)):
        name = basename(filename[1])[:-7]
        # classmap[class_idx] = name
        sample = pd.read_csv(filename[1], ',')
        sample = np.array(sample).reshape(1, len(sample))[0]
        dataset = np.append(dataset, sample)
        label = np.append(label, name)
    dataset = dataset.reshape(count, len(sample))
    return dataset, label


class cross_validation:

    def __init__(self, classifier, dataset, label, **kwargs):

        self.classifier = classifier
        self.dataset = dataset
        self.label = label
        self.__dict__.update(**kwargs)
        self.kwargs = kwargs

    def KFold(self, splits=5):

        le = LabelEncoder()
        self.int_label = (le.fit_transform(self.label))
        X, y = self.dataset, self.int_label

        cv = KFold(n_splits=splits, shuffle=True, random_state=42)
        score_array = np.array([])
        rmse_array = np.array([])
        for _ in range(10):
            for train_index, test_index in cv.split(X):
                self.train_data = X[train_index]
                self.train_label = y[train_index]
                self.test_data = X[test_index]
                self.test_label = y[test_index]
                # # lists with the parameters for the classifier SVM
                clf = self.classifier(**self.kwargs)

                clf.fit(self.train_data, self.train_label)
                pred = clf.predict(self.test_data)
                score = clf.score(self.test_data, self.test_label)
                rmse = np.sqrt(mean_squared_error(self.test_label, pred))
                score_array = np.append(score_array, score)
                rmse_array = np.append(rmse_array, rmse)

                score = np.mean(score_array)
                rmse = np.mean(rmse_array)

        print("RMSE: %f" % (rmse))
        print("Score: %f" % (score))
        classifier_performance = {
            'Name': self.classifier.__name__, **self.kwargs, 'Score': round((score*100), 2)}
        return clf, classifier_performance

    def confusion_matrix(self,dataset='All'):
        clf, _ = self.KFold()

        if dataset == 'all':
            pred = clf.predict(self.dataset)
            result = pd.DataFrame(confusion_matrix(self.int_label, pred), columns=[
                              'True motion', 'True rest'], index=['Predicted motion', 'Predicted rest'])
        elif dataset == 'test':
            pred = clf.predict(self.test_data)
            result = pd.DataFrame(confusion_matrix(self.test_label, pred), columns=[
                              'True motion', 'True rest'], index=['Predicted motion', 'Predicted rest'])
        elif dataset == 'train':
            pred = clf.predict(self.train_data)
            result = pd.DataFrame(confusion_matrix(self.train_label, pred), columns=[
                              'True motion', 'True rest'], index=['Predicted motion', 'Predicted rest'])
        

        return result


def model_selection(folder):

    dataset, label = load_features(folder)
    classifiers = [SVC, RVC, RandomForestClassifier, DecisionTreeClassifier]

    # lists with the parameters for the classifier SVM
    c_values = [0.1, 1, 10]
    kernels = ['linear', 'sigmoid', 'poly', 'rbf']
    gamma_values = [0.1, 0.01, 0.001, 0.0001]
    degree_values = [2, 3, 4]
    coef0_values = [0, 0.25, 0.5]

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
                                            _, performance = cross_validation(
                                                clf, dataset, label, **parameters).KFold()
                                            performances = performances.append(
                                                (performance), ignore_index=True)
                                            print(performance)
                                    else:
                                        parameters = {
                                            'C': C, 'kernel': kernel, 'gamma': gamma, 'coef0': coef0}
                                        _, performance = cross_validation(
                                            clf, dataset, label, **parameters).KFold()
                                        performances = performances.append(
                                            (performance), ignore_index=True)
                                        print(performance)
                            else:
                                parameters = {
                                    'C': C, 'kernel': kernel, 'gamma': gamma}
                                _, performance = cross_validation(
                                    clf, dataset, label, **parameters).KFold()
                                performances = performances.append(
                                    (performance), ignore_index=True)
                                print(performance)
                    else:
                        parameters = {'C': C, 'kernel': kernel}
                        _, performance = cross_validation(
                            clf, dataset, label, **parameters).KFold()
                        performances = performances.append(
                            (performance), ignore_index=True)
                        print(performance)

        elif clf == RVC:
            for kernel in kernels:
                for gamma in gamma_values:
                    parameters = {
                        'kernel': kernel, 'gamma': gamma}
                    _, performance = cross_validation(
                        clf, dataset, label, **parameters).KFold()
                    performances = performances.append(
                        (performance), ignore_index=True)
                    print(performance)

        elif clf == RandomForestClassifier:
            for n_estimator in n_estimators_:
                for max_depth in max_depth_:
                    parameters = {'n_estimators': n_estimator,
                                  'max_depth': max_depth}
                    _, performance = cross_validation(
                        clf, dataset, label, **parameters).KFold()
                    performances = performances.append(
                        (performance), ignore_index=True)

                    print(performance)
        else:
            _, performance = cross_validation(clf, dataset, label).KFold()
            performances = performances.append(
                (performance), ignore_index=True)

            print(performance)

    Short_list = performances.sort_values(
        by=['Score'], ascending=False).iloc[:10, :]
    pd.DataFrame(Short_list).to_csv("classifier_shortlist.csv", index=False)


if __name__ == '__main__':

    folder = "dataset"
    model_selection(folder)
    dataset, label = load_features(folder)
    classifiers_list = pd.read_csv('classifier_shortlist.csv', sep=',')

    classifiers_list.drop(['Score'], axis=1, inplace=True)

    Summery = pd.DataFrame()
    for i in range(1,3):
        clf_ = classifiers_list.iloc[-i]['Name']
        if clf_ == 'SVC':
            model = SVC
        elif clf_ == 'RVC':
            model = RVC
        elif clf_ == 'RandomForestClassifier':
            model = RandomForestClassifier
        elif clf_ == 'DecisionTreeClassifier':
            model = DecisionTreeClassifier

        
        parameters = classifiers_list.drop(['Name'], axis=1).iloc[-i]
        parameters.dropna(axis=0, inplace=True)

        


        if 'n_estimators' in parameters:
            parameters = (parameters.astype('int'))
        cross_v = cross_validation(model, dataset, label, **parameters)

        classifiers_name = (classifiers_list.iloc[-i]['Name'])
        caption_para = parameters.to_string()
        print(cross_v.confusion_matrix(dataset='all').to_latex(caption=f'{classifiers_name}_{caption_para}'))

        print(cross_v.confusion_matrix(dataset='test').to_latex(caption=f'{classifiers_name}_{caption_para}'))