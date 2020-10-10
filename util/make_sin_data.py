import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

x  = np.arange(-360,360,1)
y = np.sin(np.radians(x)) 
# plt.plot(x,y)
# plt.grid()
# plt.hlines(0, -360, 360, color = "red")
# plt.show()

df = pd.DataFrame()
df["x"] = list(x)
df["y"] = list(y)
df.to_csv("sin_data.csv",header=False, index=False)