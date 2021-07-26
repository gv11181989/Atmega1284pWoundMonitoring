# from pathlib import Path

# size = Path('model.h').stat().st_size

# print(f'{size/1024} kb')

import pandas as pd
import numpy as np

test =  pd.read_csv('dataset\motion_00.csv', ',')
test = np.array(test).reshape(-1)


print(test.tolist())