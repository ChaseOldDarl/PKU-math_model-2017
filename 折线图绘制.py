# coding=utf-8
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import ch
ch.set_ch()
scatter = pd.read_excel("large_over_cost_per.xlsx")
scatter = scatter[["difficult_answer1", "difficult_answer2", "difficult_answer3"]]
scatter = scatter.ix[[0, 13, 14, 15]]
scatter = scatter.reindex([13, 0, 14, 15])
tmps = range(40, 80, 10)
scatter["size"] = [float(x) / 100. for x in tmps]
plt.plot(scatter["size"], scatter["difficult_answer1"], "rs:", label = u"算法一")
plt.plot(scatter["size"], scatter["difficult_answer3"], "g^-.", label = u"算法二")
plt.plot(scatter["size"], scatter["difficult_answer2"], "bo--", label = u"算法三")
plt.xticks([.4, .5, .6, .7])
plt.xlabel(u"预算空间")
plt.ylabel(u"支出偏差度/千分之")
plt.legend(loc = "upper right")
#plt.show()
plt.savefig("C:\\codes\\png\\scatter\\large_cost_money.png", dpi = 400, bbox_inches = "tight")