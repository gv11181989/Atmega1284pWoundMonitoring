import pandas as pd


classifiers_list=pd.read_csv('classifier_shortlist_pca.csv', sep=',')

print(classifiers_list.to_latex())




