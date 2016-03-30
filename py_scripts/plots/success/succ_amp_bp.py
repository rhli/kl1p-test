#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
# About  : Plot Success Mean in Contourf for AMP and BP
# Author : Xiang,Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-03-30
"""

import csv

import numpy as np
import matplotlib.pyplot as plt

# get csv data
succ_array_amp_10db = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_10db/SuccessMean_AMP_10db.csv", "r"), delimiter=','))).astype('float')
succ_array_amp_20db = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/SuccessMean_AMP_20db.csv", "r"), delimiter=','))).astype('float')

succ_array_bp_10db = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_10db/SuccessMean_Basis-Pursuit_10db.csv", "r"), delimiter=','))).astype('float')
succ_array_bp_20db = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/SuccessMean_Basis-Pursuit_20db.csv", "r"), delimiter=','))).astype('float')

# get array parameters

row_num = len(succ_array_amp_10db)
col_num = len(succ_array_amp_10db[1])

# --- use contourf plot ---

# adjust subplots
plt.subplots_adjust(hspace=0.3, wspace=0.3)

# subplot 1: OMP 10db
# -----------------------------------------------------------------------------
ax1 = plt.subplot(2, 2, 1)
plt.title("AMP SNR=10db", fontsize=10)
ct1 = plt.contourf(succ_array_amp_10db, origin='lower')

# subplot 2: OMP 20db
# -----------------------------------------------------------------------------
ax2 = plt.subplot(2, 2, 2)
plt.title("AMP SNR=20db", fontsize=10)
ct2 = plt.contourf(succ_array_amp_20db, origin='lower')
cbar = plt.colorbar(ct2)

# subplot 3: CoSaMP 10db
# -----------------------------------------------------------------------------
ax3 = plt.subplot(2, 2, 3)
plt.title("BP SNR=10db", fontsize=10)
ct3 = plt.contourf(succ_array_bp_10db, origin='lower')

# subplot 4: BP 20db
# -----------------------------------------------------------------------------
ax4 = plt.subplot(2, 2, 4)
plt.title("BP SNR=20db", fontsize=10)
ct4 = plt.contourf(succ_array_bp_20db, origin='lower')
cbar = plt.colorbar(ct4)

# save picture
plt.savefig('succ_amp_bp.png', dpi=1000)
