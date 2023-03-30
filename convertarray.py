import numpy as np
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import sys
from pathlib import Path

df = pd.read_excel("C:/Users/Const/Desktop/AlgoEngResultAnalysis.xlsx",sheet_name='v2')
print(df)
array = df.iloc[:,4].values
print(array.tolist())
print("\n\n\n")
print(len(array))



