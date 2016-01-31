#!/usr/bin/python3
# -*- coding: utf-8 -*-
# #########################################################
# About  : Run CS Test using cpp programm csTest
# Author : Xiang,Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-01-31 17:20:14
# #########################################################

import os
import sys

# ---------------------------------------------------------------------------------------
# test algorithms
algorithms = ['OMP', 'ROMP', 'CoSaMP', 'Subspace-Pursuit', 'SL0', 'AMP', 'EMBP']

# init basic file paths
src_file_path = ["./csv_matrix/MSEMean_", "./csv_matrix/MSEStd_", "./csv_matrix/RunTimeMean_", "./csv_matrix/RunTimeStd_",
                 "./csv_matrix/SuccessMean_", "./csv_matrix/SuccessStd_"]

dst_file_path = ["./results_matrix/MSEMean_", "./results_matrix/MSEStd_", "./results_matrix/RunTimeMean_", "./results_matrix/RunTimeStd_",
                 "./results_matrix/SuccessMean_", "./results_matrix/SuccessStd_"]

src_file = [None] * len(src_file_path)
dst_file = [None] * len(src_file_path)
# ---------------------------------------------------------------------------------------


# main fuction
# ---------------------------------------------------------------------------------------
def main():
    try:
        print('============================================')
        print('cs algorithms testing programm started...\n')

        # get parameters
        m_min = int(input("input m_min: "))
        m_max = int(input("input m_max: "))
        k_min = int(input("input k_min: "))
        k_max = int(input("input k_max: "))
        num_rounds = int(input("input num_rounds: "))

        print('cs-algorithms list: ')
        for i in range(len(algorithms)):
            print('[%d] ' %(i + 1) + algorithms[i])

        algo_num = int(input("choose cs-algorithm(type number): "))

        # get src and dst files
        algo_name = algorithms[algo_num - 1]

        for i in range(len(src_file_path)):
            src_file_path[i] += algo_name + '.csv'

        for i in range(len(dst_file_path)):
            dst_file_path[i] += algo_name + '.csv'

        # if clean dst_file for new test
        choose = input("Do you want to clear file(y/n)? ")
        if choose == 'y':
            for file_path in dst_file_path:
                with open(file_path, 'w+') as file:
                    file.write('')
                    file.close()
        print('============================================')

        # --- run test programm ---
        for m in range(m_min, m_max + 1, 1):
            exec = "./csTest %d %d %d %d %d %d" %(m, m, k_min, k_max, num_rounds, algo_num)
            print(exec)
            os.system(exec)

            # file operations
            for j in range(len(src_file_path)):
                # get file pointer
                src_file[j] = open(src_file_path[j], 'r')
                dst_file[j] = open(dst_file_path[j], 'a')

                # write new data in results file
                read_lines = src_file[j].readlines()
                write_line = read_lines[m - 1]
                dst_file[j].write(write_line)

        for i in range(len(src_file)):
            src_file[i].close()
            dst_file[i].close()

    except KeyboardInterrupt:
        print("Get KeyboardInterrupt")
        sys.exit(0)
# ---------------------------------------------------------------------------------------

if __name__ == '__main__':
    main()
