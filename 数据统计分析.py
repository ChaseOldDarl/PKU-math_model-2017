# coding=utf-8
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import ch
ch.set_ch()
#f_std = open("C:\\precious_data\\answers\\rate_seller_0.5_0.6.msk")
f_check1 = open("C:\\precious_data\\difficult_answer1\\money_0.35.msk")
f_check2 = open("C:\\precious_data\\difficult_answer2\\money_0.35.msk")
f_check3 = open("C:\\precious_data\\difficult_answer3\\money_0.35.msk")
count1 = []
count2 = []
count3 = []
rate1 = 0
rate2 = 0
rate3 = 0
while True:
    line11 = f_check1.readline()
    if len(line11) == 0:
        break
    line12 = f_check1.readline()
    line21 = f_check2.readline()
    line22 = f_check2.readline()
    line31 = f_check3.readline()
    line32 = f_check3.readline()
    item1, cost1 = line11.split()
    item2, cost2 = line21.split()
    item3, cost3 = line31.split()
    item0, cost0 = item2, cost2
    if int(item1) > int(item0) or (int(item1) == int(item0) and int(cost1) < int(cost0)):
        item0 = item1
        cost0 = cost1
    if int(item3) > int(item0) or (int(item3) == int(item0) and int(cost3) < int(cost0)):
        item0 = item3
        cost0 = cost3
    flag = True
    if int(item0) - int(item1) == 0:
        rate1 += 1
    else:
        flag = False
    if int(item0) - int(item2) == 0:
        rate2 += 1
    else:
        flag = False
    if int(item0) - int(item3) == 0:
        rate3 += 1
    else:
        flag = False
    if flag:
        count1.append(float(1000) * (float(cost1) - float(cost0)) / float(cost0))
        count2.append(float(1000) * (float(cost2) - float(cost0)) / float(cost0))
        count3.append(float(1000) * (float(cost3) - float(cost0)) / float(cost0))
rate1 = float(rate1) / float(1000)
rate2 = float(rate2) / float(1000)
rate3 = float(rate3) / float(1000)
count1 = pd.Series(count1)
mean1 = count1.mean()
max1 = 5 * count1.std()
count11 = [x for x in count1]
for x in count11:
    if x > mean1 + max1:
        count11.remove(x)
count11 = pd.Series(count11)
count2 = pd.Series(count2)
mean2 = count2.mean()
max2 = 5 * count2.std()
count22 = [x for x in count2]
for x in count22:
    if x > mean2 + max2:
        count22.remove(x)
count22 = pd.Series(count22)
count3 = pd.Series(count3)
mean3 = count3.mean()
max3 = 5 * count3.std()
count33 = [x for x in count3]
for x in count33:
    if x > mean3 + max3:
        count33.remove(x)
count33 = pd.Series(count33)
print rate1, count11.mean()
print rate2, count22.mean()
print rate3, count33.mean()