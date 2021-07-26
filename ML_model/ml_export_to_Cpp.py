import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
from model_selection import load_features, classifier,model_selection
from micromlgen import port
import json
from pathlib import Path

model_selection('dataset')

dataset, label, classmap = load_features('dataset')


classifiers_list = pd.read_csv('classifier_shortlist.csv', sep=',')
classifiers_list.drop(['Score'], axis=1, inplace=True)
classifiers_list.dropna(axis=1, inplace=True)

classifiers = [SVC, RandomForestClassifier, DecisionTreeClassifier]

Summery = pd.DataFrame()
for i in range(5):
    clf_ = classifiers_list.loc[i]['Name']
    model = classifiers[classifiers == clf_]

    parameters = classifiers_list.drop(['Name'], axis=1).loc[i].to_dict()

    clf, _ = classifier(model, dataset, label, **parameters)
    file_name = json.dumps(parameters)
    file_name = file_name.replace('{', '').replace('"', '').replace(
        ',', '').replace('}', '').replace(':', '').replace(' ', '_')

    c_code = port(clf, classmap=classmap)
    with open(f'model_{clf_}_{file_name}.h', "w") as text_file:
        text_file.write(c_code)

    size = Path(f'model_{clf_}_{file_name}.h').stat().st_size
    Summery = Summery.append({
        'Model' :  f'model_{clf_}_{file_name}',
        'Size_KBs' : size/1024
    },ignore_index=True)


Best_performance = Summery.sort_values(by = ['Size_KBs'],ascending=False).iloc[0]
Best_model = Best_performance['Model']
Best_model_size = round(Best_performance['Size_KBs'],2)

print(f'Best model is {Best_model}.\nThe size of Model is {Best_model_size} KBs')