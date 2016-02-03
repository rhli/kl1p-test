#!/usr/bin/python3
# -*- coding: utf-8 -*-
# #####################################
# Author : Xiang,Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-01-27 07:34:49
# About  : Plot MSE results from CSV
# #####################################

import csv

import numpy as np
from matplotlib import pyplot as plt

# get mse data
mse_mean_array = np.array(list(csv.reader(open("../../test_results/without_noise/MSEMean_OMP.csv", "r"), delimiter=','))).astype('float')
mse_std_array= np.array(list(csv.reader(open("../../test_results/without_noise/MSEStd_OMP.csv", "r"), delimiter=','))).astype('float')

#  print(success_mean_array)

# Get array parameters
row_num = len(mse_mean_array)
col_num = len(mse_mean_array[1])

# Get settings
choose = input("\nPlot column(m) or row(k): ")

if choose == 'm':
    sel_col_num = input("\nInput col number to plot: ")
    sel_col_num = int(sel_col_num)
    sel_col = mse_mean_array[:, sel_col_num - 1]
    x_axis = np.arange(1, row_num + 1, 1)
    y_axis = sel_col
    #  plt.plot(x_axis, y_axis, color='black', label='', lw=1, ls='-', marker='s', markerfacecolor='None', markeredgewidth=1, markeredgecolor='black')
    plt.plot(x_axis, y_axis, color='black', label='', lw=1, ls='-')

    # settings for the figure
    plt.title("MSE with K = " + str(sel_col_num))
    plt.xlabel("number of mesurament -> k")
    plt.ylabel("MSE")
    plt.legend(loc='upper left', prop={'size': 12})
    plt.grid()

    plt.savefig('./k' + str(sel_col_num) + '.png', dpi=1000)

if choose == 'k':
    sel_row_num = input("\nInput row number to plot: ")
    sel_row_num = int(sel_row_num)
    sel_row = mse_mean_array[sel_row_num - 1, :]
    sel_row_std = mse_std_array[sel_row_num -1, :]
    #  print(sel_row_std)

    x_axis = np.arange(1, col_num + 1, 1)
    y_axis = sel_row

    # calc the half width of confidence interval(using student-distribution)
    num_sim = 100
    t_factor = 2.626  # 99% for two sided

    for i in range(len(sel_row_std)):
        sel_row_std[i] = (t_factor * sel_row_std[i]) / np.sqrt(num_sim)

    y_error = sel_row_std
    #  print(y_error)

    #  plt.plot(x_axis, y_axis, color='black', label='', lw=1.5, ls='-', marker='o', markerfacecolor='None', markeredgewidth=1.5, markeredgecolor='black')
    plt.errorbar(x_axis, y_axis, yerr=y_error, color='black', label='', lw=1.5, ls='-', marker='o', markerfacecolor='None', markeredgewidth=1.5, markeredgecolor='black')

    # settings for the figure
    plt.title("MSE with K = " + str(sel_row_num))
    plt.xlabel("sparcity of signal -> k")
    plt.ylabel("MSE")
    # set extrem value on x and y axis
    #  plt.ylim(0, 2200)
    #  plt.xlim(30, 70)
    #  plt.legend(loc='upper left', prop={'size': 12})
    plt.grid()

    plt.savefig('./m' + str(sel_row_num) + '.png', dpi=1000)
