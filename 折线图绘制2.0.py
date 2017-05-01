# coding=utf-8
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import ch
ch.set_ch()
time = pd.read_excel("time.xlsx")
save = time[["difficult_answer1", "difficult_answer2", "difficult_answer3"]]
save = save.ix[[0, 13 ,14 ,15]]
save = save.reindex([13, 0, 14, 15])
tmps = range(4, 8, 1)
save["size"] = [float(x) / 10. for x in tmps]
plt.plot(save["size"], save["difficult_answer1"], "rs:", label = u"算法一")
plt.plot(save["size"], save["difficult_answer3"], "g^-.", label = u"算法二")
plt.plot(save["size"], save["difficult_answer2"], "bo--", label = u"算法三")
plt.xlabel(u"预算空间")
plt.ylabel(u"算法用时/（秒/千次）")
plt.xticks([0.4, 0.5, 0.6, 0.7])
plt.legend(loc = "upper left")
plt.show()
#plt.savefig("C:\\codes\\png\\time_money--.png", dpi = 400, bbox_inches = "tight")