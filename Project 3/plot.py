import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
result_file="Project 3/results/table1.csv"
result_data=pd.read_csv(result_file)
result_df=pd.DataFrame(result_data)

#p1=sns.relplot( kind="line",data=result_df,y="Latency avg (usec)",x="IOPS(k)",hue="Block Size(KiB)")
#p2=sns.relplot( kind="line",data=result_df,y="Latency avg (usec)",x="IOPS(k)",hue="Percentage of Write(%)")
#p3=sns.relplot( kind="line",data=result_df,y="Latency avg (usec)",x="IOPS(k)",hue="IO Depth")
p1=sns.lmplot(data=result_df,x="Latency avg (usec)",y="IOPS(k)",hue="Block Size(KiB)")
p1=sns.lmplot(data=result_df,x="Latency avg (usec)",y="IOPS(k)",hue="Percentage of Write(%)")
p1=sns.lmplot(data=result_df,x="Latency avg (usec)",y="IOPS(k)",hue="IO Depth")
plt.show()
print(result_df)