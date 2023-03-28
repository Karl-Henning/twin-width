import re
import datetime
import pandas
import numpy as np
import matplotlib.pyplot as plt
import os
import math

# list of logfiles for which graphs are to be generated  (that are converted into txt files) 
names = ["log","twin-width_greedy","twin-width_newAlgo_2017_001-100"]
for name in names:
  #open the log file and extract all the information given 
  with open(name+".txt") as f:
    lines = f.readlines()
    b=[None]*len(lines)
    c=[None]*len(lines)
    time_in_s=[None]*len(lines)
    for i in range(len(lines)+1):

      
      if i < 10:
        lines[i-1]= lines[i-1].removeprefix('heuristic/he00'+str(i)+".gr, runtime: ")
        lines[i-1] = ''.join(x for x in lines[i-1] if x.isdigit() or x == "." or x == " " or x=="s" or x=="m")
        

      if i >= 10:
        lines[i-1]= lines[i-1].removeprefix('heuristic/he0'+str(i)+".gr, runtime: ")
        lines[i-1] = ''.join(x for x in lines[i-1] if x.isdigit() or x == "." or x == " " or x=="s" or x=="m") 
      if i >= 100:
        lines[i-1]= lines[i-1].removeprefix('heuristic/he'+str(i)+".gr, runtime: ")
        lines[i-1] = ''.join(x for x in lines[i-1] if x.isdigit() or x == "." or x == " " or x=="s" or x=="m")
        
        lines[i-1]= lines[i-1].removeprefix("s"+str(i)+". m")
    for i in range(len(lines)-1):
      a = lines[i].split()
      
    # b and c are temprorary variables that store the time and twin width data 
      b[i] = a[0]
      c[i] = int(a[1])
      #TODO: the last value of c is always negative needs to be chnaged
      time_in_s = [None]*(len(lines)-1)

    #convert the runt time information into time in seconds 
    for i in range(len(b)-1):
        if  b[i].endswith("ms"):
          b[i]= b[i][:-2]
          temp = float(b[i])/1000
          time_in_s[i] = math.log(temp) 

        elif b[i].endswith("s"):
          b[i]= b[i][:-1]
          temp = float(b[i])
          time_in_s[i] = math.log(temp)

        elif b[i].endswith("m"):
          b[i]= b[i][:-1]
          temp = float(b[i])*60
          time_in_s[i] = math.log(temp)

        else:
          time_in_s[i]= 0

    vertices =[9, 408, 391, 408, 22, 199, 524, 580, 806, 146, 1795, 1614, 1845, 1451, 1644, 1523, 1714, 1472, 1771, 1503, 1400, 1479, 2044, 1419, 1419, 1397, 1797, 1455, 1785, 1283, 1223, 1348, 1187, 1436, 1334, 1522, 1704, 1128, 1213, 4596, 4403, 2428, 4053, 736, 842, 1425, 2932, 2992, 505, 1230, 1948, 642, 993, 240, 475, 168, 280, 168, 224, 280, 240, 189, 810, 408, 269, 1265, 968, 336, 850, 850, 1261, 1750, 1100, 3630, 1800, 135, 126, 6961, 6961, 175, 153, 756, 476, 4373, 3501, 4007, 3752, 4215, 3275, 2898, 3354, 3574, 3854, 3210, 3291, 3425, 2922, 3714, 7638, 62500, 30000, 9422, 9891, 11416, 11805, 12568, 12601, 21206, 14096, 14629, 79799, 25008, 20220, 25071, 23068, 23479, 18536, 23502, 32718, 29837, 21271, 14352, 15872, 14558, 23556, 23538, 23549, 23475, 43942, 29919, 15671, 14847, 48224, 32272, 33512, 34905, 36318, 51995, 69870, 59932, 70618, 94730, 104145, 66385, 156178, 71409, 394687, 94695, 172988, 92564, 94663, 217600, 137293, 192918, 180273, 227964, 203719, 863026, 229848, 462976, 254892, 336775, 382177, 778291, 349119, 471387, 620597, 730055, 1581796, 553709, 1021421, 742488, 1407590, 3045298, 2599017, 1372958, 1400461, 1502498, 3876484, 1095148, 5335679, 1140516, 7293450, 5897750, 1887871, 1889177, 2032996, 4299945, 1674970, 11684393, 2048135, 18105276, 7292600, 3511798, 6367972, 7502740, 19826100, 7583653, 13149385, 23824624]
    vertices =np.array(vertices[1:len(c)])
    edges =[7, 172, 167, 172, 13, 111, 303, 332, 452, 82, 900, 921, 988, 739, 916, 790, 840, 762, 926, 849, 717, 735, 1149, 773, 742, 725, 1024, 786, 1069, 661, 630, 676, 614, 836, 714, 817, 1003, 604, 603, 196, 307, 179, 299, 125, 199, 340, 239, 363, 95, 192, 751, 193, 378, 51, 100, 112, 56, 112, 64, 56, 120, 126, 81, 68, 100, 121, 81, 112, 85, 85, 96, 144, 100, 121, 100, 90, 42, 125, 125, 50, 102, 56, 49, 2113, 1751, 1996, 1847, 2030, 1692, 1558, 1692, 1848, 1910, 1684, 1643, 1675, 1545, 708, 2835, 500, 10200, 823, 819, 1236, 1194, 4660, 2228, 1160, 1660, 1133, 400, 3228, 1952, 1178, 8749, 2200, 6040, 2200, 3745, 1266, 1962, 7343, 7900, 7420, 2200, 2200, 2200, 2200, 4575, 2257, 7833, 7565, 3952, 1995, 8282, 8591, 8905, 17307, 7865, 20103, 11680, 9600, 10531, 23695, 10420, 26328, 7502, 34033, 2856, 31473, 32188, 72835, 49282, 66421, 69371, 85646, 127574, 6220, 144314, 62914, 154188, 95695, 95078, 20446, 11304, 129128, 155352, 124208, 273548, 351267, 373241, 468913, 302023, 105424, 69789, 225885, 199998, 578891, 134176, 685591, 77639, 716109, 107436, 1484059, 258776, 259611, 381703, 106013, 1035685, 89315, 1292729, 178719, 109684, 2214260, 1312237, 1546096, 222845, 4732056, 8242420, 15531867]
    edges =np.array(edges[1:len(c)])
    density = edges[:] / vertices[:]

    area = 50
    plt.rcParams["figure.figsize"]=(30 , 20)
    
    #plot graph that shows the correlation between time and vertices
    plt.scatter(c[:-1],edges,s=area, label=name)
    plt.legend()
    plt.xlabel('twin_width')
    plt.ylabel('edges')
    plt.savefig('twinwidth_edges.png')
    
    plt.grid(True)
plt.close()
