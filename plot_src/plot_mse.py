#!/usr/bin/env python
# -*- coding: utf-8 -*-
# #####################################
# Author : Xiang,Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-01-27 07:34:49
# About  : Plot MSE results from CSV
# #####################################

import csv

import numpy as np
#  from matplotlib import pyplot as plt

# Read data from a CSV file
mse_mean_array = np.array(list(csv.reader(open("../csv_matrix/MSEMean_OMP.csv", "r"), delimiter=','))).astype('float')
runtime_mean_array = np.array(list(csv.reader(open("../csv_matrix/RunTimeMean_OMP.csv", "r"), delimiter=','))).astype('float')
success_mean_array = np.array(list(csv.reader(open("../csv_matrix/SuccessMean_OMP.csv", "r"), delimiter=','))).astype('float')

input("Plot ")

# Get array parameters
row_num = len(mse_mean_array)
col_num = len(mse_mean_array[1])

# Choose column or row for ploting from array
select_col = col_num

# Plot results

#  m_index = np.arange(1, len(column_k_max) + 1, 1)
#  plt.plot(m_index, column_k_max, color='black', label='Pakete vom Helfer', lw=1, ls='-', marker='s', markerfacecolor='None', markeredgewidth=1, markeredgecolor='black')

#  plt.show()
