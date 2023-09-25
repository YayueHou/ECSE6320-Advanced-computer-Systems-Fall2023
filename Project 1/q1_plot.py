import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
result_file="./mlc_zero-queue.csv"
result_data=pd.read_csv(result_file)
result_df=pd.DataFrame(result_data)

p1=sns.relplot( kind="line",data=result_df,x="Buffer_size(MiB)",y="Latency(ns)")

plt.show()
print(result_df)