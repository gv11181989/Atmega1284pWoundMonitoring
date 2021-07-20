import numpy as np
import pandas as pd
from sklearn.svm import SVC
from sklearn.model_selection import KFold
from sklearn.datasets import load_iris

global counter
counter = 0
class Classification:
    """This class holds different classification algorithms
    and the cv function
    """

    def __init__(self,X,y):  
        """Initializing
        
        Parameters
        ----------
        X : array-like, shape (n_samples, feature_dim)
            The data for the cross validation
        y : array-like, shape (n-samples, label_dim)
            The labels of the data used in the cross validation
        """
        X_mean = X.mean(axis=0)
        X = X - X_mean        
        self.X = X
        self.y = y
    
    def apply_k_fold_cv(self, classifier, n_folds=5, c_value=1.0, kernel_='rbf', \
                        gamma_value=1.0, coef0_value=1.0, degree_value=3):
        """K fold cross validation.
        
        Parameters
        ----------
        classifier : function
            The function that is used for classification of
            the training data
            
        n_splits : int, optional (default: 5)
            The number of folds for the cross validation
            
        c_value : float (default: 1.0)
            C value for the SVM
        
        kernel_ : string (default: 'rbf')
            kernel function for the SVM  
            
        gamma_value : float (default: 1.0)
            gamma value for the SVM
            
        coef0_value : float (default: 1.0)
            coef0 value for the SVM
                        
        degree_value : int (default: 3)
            degree value for the SVM
            
        Returns
        -------
        scores : array, shape (n_splits,)
            Vector of classification accuracies for the n_splits folds.
        """
        X = self.X 
        y = self.y

        assert X.shape[0] == y.shape[0]

        if len(X.shape) < 2:
            X = np.atleast_2d(X).T
        if len(y.shape) < 2:
            y = np.atleast_2d(y).T

        cv = KFold(n_splits=n_folds, shuffle=True, random_state=42)
        scores = []

        for train_index, test_index in cv.split(X):
            train_data = X[train_index, :]
            train_label = y[train_index, :]
            test_data = X[test_index, :]
            test_label = y[test_index, :]
            
            train_label = np.ravel(train_label)
            
            score = classifier(train_data, test_data, train_label, test_label, \
                               c_value, kernel_, gamma_value, coef0_value, degree_value)

            scores.append(score)

        return np.array(scores)
    
    def support_vector_machine(self, train_data, test_data, train_label, \
                               test_label, c_value=1.0, kernel_='rbf', \
                               gamma_value=1.0, coef0_value=1.0, degree_value=3):
        """Support Vector Machine classifier.
        
        Parameters
        ----------
        train_data : array-like, shape (n_samples, feature_dim)
            The training data for the classifier SVM
            
        test_data : array-like, shape (n-samples, feature_dim)
            The test data for the classifier SVM
            
        train_label : array-like, shape (n_samples, label_dim)
            The labels of the training data
            
        test_data : array-like, shape (n-samples, label_dim)
            The labels of the test data
            
        c_value : float (default: 1.0)
            C value for the SVM
        
        kernel_ : string (default: 'rbf')
            kernel function for the SVM  
            
        gamma_value : float (default: 1.0)
            gamma value for the SVM
            
        coef0_value : float (default: 1.0)
            coef0 value for the SVM
                        
        degree_value : int (default: 3)
            degree value for the SVM
        Returns
        -------
        score : float
            Classification accuracy of one fold of the cross validation.
        """
       
        # initialising the classifier SVM
        classifier = SVC(C=c_value, kernel=kernel_, gamma=gamma_value, \
                         coef0=coef0_value, degree=degree_value)
        # training it on the training data
        classifier.fit(train_data, train_label)
        # testing it with the test data
        score = classifier.score(test_data, test_label)
        
        return score
    
    def find_ideal_params(self, k=5):
        """Function for finding the ideal parameters gaining the highest performance for SVM.
        Parameters
        ----------
        k : int (default: 5)
            Amount of folds for the Cross Validation

        Returns
        -------
        max_performance : float
            Maximum performance.
        
        ideal_parameters : Dataframe (pandas), shape (n_parameter_tests, 6)
            Dataframe with the ideal parameters for SVM.
            
            
        max_row_possibility: Dataframe (pandas), shape (1, 6)
            First set of ideal parameters for task 4.1 e)
        """


        # lists with the parameters for the classifier SVM
        c_values = [0.1, 1, 10, 100, 1000, 10000]
        kernels = ['linear', 'rbf', 'sigmoid', 'poly']
        gamma_values = [1, 0.1, 0.01, 0.001, 0.0001]
        degree_values = [2, 3, 4, 5, 6]
        coef0_values = [0, 0.25, 0.5, 0.75, 1]
        
        # for each parameter run SVM
        performances = []
        for kernel_ in kernels:
            for c_value in c_values:
                
                # run different gamma values just if necessary (Gaussian, polynominal, sigmoid)
                if kernel_ == 'rbf' or kernel_ == 'poly' or kernel_ == 'sigmoid':
                    for gamma_value in gamma_values:
                        
                        # run different coef0 values just if necessary (polynominal, sigmoid)
                        if kernel_ == 'poly' or kernel_ == 'sigmoid':
                            for coef0_value in coef0_values:
                            
                                # run different degree values just if necessary (polynominal)
                                if kernel_ == 'poly':
                                    for degree_value in degree_values:                            
                                        
                                            # find scores of the SVM for n_fold cross validation
                                            scores = self.apply_k_fold_cv(self.support_vector_machine, k, \
                                                                    c_value, kernel_, gamma_value, \
                                                                    coef0_value, degree_value)
                                            # calculate the performance (all n_folds)
                                            performance = float(sum(scores)/len(scores))
                                            # add performane with their belonging parameters to list performances
                                            performances.append([kernel_, c_value, gamma_value, coef0_value, \
                                                                degree_value, performance])  
                                        
                                else:
                                    # find scores of the SVM for n_fold cross validation
                                    scores = self.apply_k_fold_cv(self.support_vector_machine, k, \
                                                               c_value, kernel_, gamma_value, \
                                                               coef0_value)
                                    # calculate the performance (all n_folds)
                                    performance = float(sum(scores)/len(scores))
                                    # add performane with their belonging parameters to list performances
                                    performances.append([kernel_, c_value, gamma_value, coef0_value, \
                                                            'x', performance])
                                    
                        else:
                            # find scores of the SVM for n_fold cross validation
                            scores = self.apply_k_fold_cv(self.support_vector_machine, k, \
                                                       c_value, kernel_, gamma_value)
                            # calculate the performance (all n_folds)
                            performance = float(sum(scores)/len(scores))
                            # add performane with their belonging parameters to list performances
                            performances.append([kernel_, c_value, gamma_value, 'x', \
                                                'x', performance])
                            
                else:
                    # find scores of the SVM for n_fold cross validation
                    scores = self.apply_k_fold_cv(self.support_vector_machine, k, \
                                               c_value, kernel_)
                    # calculate the performance (all n_folds)
                    performance = float(sum(scores)/len(scores))
                    # add performane with their belonging parameters to list performances
                    performances.append([kernel_, c_value, 'x', 'x', \
                                        'x', performance])
        
        # convert list performances to a numpy array
        np_performances = np.array(performances)
        
        # find the maximum performances
        max_performance = max(np_performances.T[5])
        
        # convert the numpy performances array to a pandas dataframe for visuality
        df = pd.DataFrame({'Kernel': np_performances[:, 0], 'C': np_performances[:, 1], \
                           'gamma': np_performances[:, 2], 'coef0': np_performances[:, 3], \
                           'degree': np_performances[:, 4], 'Performance': np_performances[:, 5]})
        
        # create Dataframe with just the ideal parameters
        ideal_parameters = df[df['Performance'] == max_performance]
        
        # for problem 4.1 e) just one row is needed
        max_row_possibility_index = (df.Performance.values == max_performance).argmax()
        max_row_possibility = df.loc[max_row_possibility_index]
        
        # give the result out (print)
        print("The maximum performance is ", max_performance)
        print("The ideal parameters are:")
        print(ideal_parameters)
         
        return max_performance, ideal_parameters, max_row_possibility


if __name__ == '__main__':
    
    from ml_inference import load_features
    from sklearn.preprocessing import LabelEncoder, normalize

    folder = 'dataset'
    dataset, label,classmap = load_features(folder)
    le = LabelEncoder()
    int_label = (le.fit_transform(label))
    X, y = dataset, int_label
    from sklearn.decomposition import PCA
    pca = PCA(n_components=2)
    # X = normalize(X, norm='l2', axis=1, copy=True, return_norm=False)
    # pca.fit(X)
    # X = pca.transform(X)
       
    c = Classification(X,y)
    
    # calling function find_ideal_params to find ideal parameters for the SVM
    max_performance, ideal_parameters, max_row_possibility = c.find_ideal_params(k=15)