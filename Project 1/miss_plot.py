import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
result_file="./miss_out.csv"
result_data=pd.read_csv(result_file)
result_df=pd.DataFrame(result_data)

p1=sns.lmplot(data=result_df,x="cache_miss_ratio(%)",y="runtime(ms)")
p2=sns.lmplot(data=result_df,x="dTLB_miss_ratio(%)",y="runtime(ms)")
plt.show()
print(result_df)