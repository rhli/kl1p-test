#!/usr/bin/python3
# -*- coding: utf-8 -*-
# #########################################################
# Author : Xiang,Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-01-27 19:08:26
# About  : Run CS Test and data Proc with Pause
# #########################################################

import os
import sys

# init file paths
src_file_path = ["./csv_matrix/MSEMean_OMP.csv", "./csv_matrix/MSEStd_OMP.csv", "./csv_matrix/RunTimeMean_OMP.csv", "./csv_matrix/RunTimeStd_OMP.csv",
                 "./csv_matrix/SuccessMean_OMP.csv", "./csv_matrix/SuccessStd_OMP.csv"]

dst_file_path = ["./results_matrix/MSEMean_OMP.csv", "./results_matrix/MSEStd_OMP.csv", "./results_matrix/RunTimeMean_OMP.csv", "./results_matrix/RunTimeStd_OMP.csv",
                 "./results_matrix/SuccessMean_OMP.csv", "./results_matrix/SuccessStd_OMP.csv"]

src_file = [None] * len(src_file_path)
dst_file = [None] * len(src_file_path)


# main fuction
# ---------------------------------------------------------------------------------------
def main():
    try:

        choose = input("Do you want to clear file(y/n)? ")
        if choose == 'y':
            for file_path in dst_file_path:
                with open(file_path, 'w+') as file:
                    file.write('')
                    file.close()

        m_min = int(input("input m_min: "))
        m_max = int(input("input m_max: "))

        # init parameters
        k_min = 1
        k_max = 30
        run_time = 1
        algo_num = 1

        # run test programm
        for m in range(m_min, m_max + 1, 1):
            exec = "./csTest %d %d %d %d %d %d" %(m, m, k_min, k_max, run_time, algo_num)
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
