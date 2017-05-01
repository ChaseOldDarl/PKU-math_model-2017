# coding=utf-8
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math
import ch
ch.set_ch()
time = pd.read_excel("time.xlsx")
save = time[["difficult_answer1", "difficult_answer2", "difficult_answer3"]]
save = save.ix[[0, 9, 10, 11]]
save = save.reindex([9, 10, 11, 0])
save["size"] = range(20, 60, 10)
plt.plot(save["size"], save["difficult_answer1"], "rs", label = "_nolegend_")
plt.plot(save["size"], save["difficult_answer3"], "g^", label = "_nolegend_")
plt.plot(save["size"], save["difficult_answer2"], "bo", label = "_nolegend_")
plt.xlabel(u"数据规模")
plt.ylabel(u"算法用时/（秒/千次）")
save["log1"] = [math.log(x) for x in save["difficult_answer1"]]
save["log2"] = [math.log(x) for x in save["difficult_answer3"]]
save["log3"] = [math.log(x) for x in save["difficult_answer2"]]
corr1 = save["log1"].corr(save["size"])
corr2 = save["log2"].corr(save["size"])
corr3 = save["log3"].corr(save["size"])
b1 = save["log1"].cov(save["size"]) / save["size"].var()
b2 = save["log2"].cov(save["size"]) / save["size"].var()
b3 = save["log3"].cov(save["size"]) / save["size"].var()
a1 = save["log1"].mean() - b1 * save["size"].mean()
a2 = save["log2"].mean() - b2 * save["size"].mean()
a3 = save["log3"].mean() - b3 * save["size"].mean()
x_test = range(15, 56, 1)
y1 = [math.exp(b1 * item + a1) for item in x_test]
y2 = [math.exp(b2 * item + a2) for item in x_test]
y3 = [math.exp(b3 * item + a3) for item in x_test]
plt.plot(x_test, y1, "r:", label=u"算法一")
plt.plot(x_test, y2, "g-.", label=u"算法二")
plt.plot(x_test, y3, "b--", label=u"算法三")
plt.xticks([20, 30, 40, 50])
ax = plt.gca()
ax.set_xticklabels(["Size(20,40)", "Size(30,60)", "Size(40,80)", "Size(50,100)"], rotation = 10, fontsize = "small")
plt.legend(loc = "upper left")
plt.show()
#plt.savefig("C:\\codes\\png\\time1_2~.png", dpi = 400, bbox_inches = "tight")