import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("nums.csv")

df.plot.scatter(x=0, y=1)
plt.show()
