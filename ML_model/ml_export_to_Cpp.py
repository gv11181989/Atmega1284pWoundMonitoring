import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
from model_selection import load_features, cross_validation,model_selection
from micromlgen import port
from pathlib import Path
from skbayes.rvm_ard_models import RVC
import numpy as np

folder = "dataset"
dataset, label = load_features(folder)
model_selection(dataset, label)
thirdclass = np.full(dataset[0].shape,10).reshape(1,45)
dataset = np.append(dataset,thirdclass,axis=0)
label = np.append(label,'temp')


classifiers_list = pd.read_csv('classifier_shortlist.csv', sep=',')


classifiers_list.drop(['Score'], axis=1, inplace=True)

Summery = pd.DataFrame()
for i in range(5):
    clf_ = classifiers_list.loc[i]['Name']
    if clf_ == 'SVC':
        model = SVC
    elif clf_ == 'RVC':
        model = RVC
    elif clf_ == 'RandomForestClassifier':
        model = RandomForestClassifier
    elif clf_ == 'DecisionTreeClassifier':
        model = DecisionTreeClassifier

    
    parameters = classifiers_list.drop(['Name'], axis=1).loc[i]
    parameters.dropna(axis=0, inplace=True)

    clf, _ = cross_validation(model, dataset, label, **parameters).KFold()
    file_name = parameters.to_json()
    file_name = file_name.replace('{','').replace('"', '').replace(
        ',', '_').replace('}','').replace(':','_').replace(' ', '_')

    c_code = port(clf)
    with open(f'model_{clf_}_{file_name}.h', "w") as text_file:
        text_file.write(c_code)

    size = Path(f'model_{clf_}_{file_name}.h').stat().st_size
    Summery = Summery.append({
        'Model' :  f'model_{clf_}_{file_name}',
        'Size_bytes' : int(size)
    },ignore_index=True)


Best_performance = Summery.sort_values(by = ['Size_bytes'],ascending=True).iloc[0]
Summery_ascending = Summery.sort_values(by = ['Size_bytes'],ascending=True)
pd.DataFrame(Summery_ascending).to_csv("Summery.csv", index=False)
Best_model = Best_performance['Model']
Best_model_size = round(Best_performance['Size_bytes'],3)


print(Summery_ascending.to_latex())

print(f'Best model is {Best_model}.\nThe size of Model is {Best_model_size} bytes')