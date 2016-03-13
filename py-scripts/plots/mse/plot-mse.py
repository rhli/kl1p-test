#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
# Author : Xiang,Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-03-13
# About  : Plot MSE results from a CSV file
"""

import csv

import numpy as np
import matplotlib.pyplot as plt

# get csv data
mean_array_omp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_10db/MSEMean_OMP_10db.csv", "r"), delimiter=','))).astype('float')
std_array_omp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_10db/MSEStd_OMP_10db.csv", "r"), delimiter=','))).astype('float')

# get csv data
mean_array_cosamp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_10db/MSEMean_CoSaMP_10db.csv", "r"), delimiter=','))).astype('float')
std_array_cosamp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_10db/MSEStd_CoSaMP_10db.csv", "r"), delimiter=','))).astype('float')

# get array parameters
row_num = len(mean_array_omp)
col_num = len(mean_array_omp[1])

print(row_num, col_num)

# subplot 1
# -----------------------------------------------------------------------------
plt.subplot(2, 2, 1)

k_10 = mean_array_omp[:, 9]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_10
plt.plot(x_axis, y_axis, color='black', label='', lw=1, ls='-',
         marker='o', markerfacecolor='None', markeredgewidth=1, markeredgecolor='black', markevery=10)
# -----------------------------------------------------------------------------

# subplot 2
# -----------------------------------------------------------------------------
plt.subplot(2, 2, 2)

k_30 = mean_array_omp[:, 30]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_30
plt.plot(x_axis, y_axis, color='black', label='', lw=1, ls='-',
         marker='o', markerfacecolor='None', markeredgewidth=1, markeredgecolor='black', markevery=10)
# -----------------------------------------------------------------------------

# subplot 3
# -----------------------------------------------------------------------------
plt.subplot(2, 2, 3)

k_10 = mean_array_cosamp[:, 10]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_10
plt.plot(x_axis, y_axis, color='black', label='', lw=1, ls='-',
         marker='o', markerfacecolor='None', markeredgewidth=1, markeredgecolor='black', markevery=10)
# -----------------------------------------------------------------------------

# subplot 4
# -----------------------------------------------------------------------------
plt.subplot(2, 2, 4)

k_30 = mean_array_cosamp[:, 30]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_30
plt.plot(x_axis, y_axis, color='black', label='', lw=1, ls='-',
         marker='o', markerfacecolor='None', markeredgewidth=1, markeredgecolor='black', markevery=10)
# -----------------------------------------------------------------------------

# save picture
plt.savefig('mse_1.png', dpi=1000)
