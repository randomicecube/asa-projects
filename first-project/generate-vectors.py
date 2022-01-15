#! /usr/bin/python

import sys
from random import random
from math import log

# def vector_generator():
#     for _ in range(n):
#         print("{}".format(int(random() * 100)), end = "")
#         if (_ != n - 1):
#             print(" ", end = "")
#     print("\n", end="")

# problem = int(sys.argv[1])
# n = int(sys.argv[2])
# noTimes = int(sys.argv[3])

# for _ in range(noTimes):
#     print("{}".format(problem))
#     vector_generator()
#     if problem == 2:
#         vector_generator()

print("1")
# 
for i in range(1,int(sys.argv[1])+1):
    print(i, end="")
    if i != int(sys.argv[1]):
        print(" ", end="")
# n = int(sys.argv[1])
# print(int(n*n))
