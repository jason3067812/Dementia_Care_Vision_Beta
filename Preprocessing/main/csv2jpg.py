#!/usr/bin/env python
# coding: utf-8

import numpy as np
from numpy import genfromtxt
import os
import cv2

if __name__=="__main__":

    while True:

        print(" ")
        date = input("please enter csv date (ex:20210819)：")
        print(" ")
        print("Below press enter represents default")
        directory_name = input("please enter input csv directory (default: out)：")
        save_directory = input("please enter save file (default: out_image)：")


        if directory_name == "":
            directory_name = "out"
        if save_directory == "":
            save_directory = "out_image"

        save_directory_1 = save_directory + "/" + "normal_img"
        save_directory_2 = save_directory + "/" + "notice_img"

        if not os.path.isdir(save_directory):
            print(f"creating directory: {save_directory}")
            os.mkdir(save_directory)
        if not os.path.isdir(save_directory_1):
            print(f"creating directory: {save_directory_1}")
            os.mkdir(save_directory_1)
        if not os.path.isdir(save_directory_2):
            print(f"creating directory: {save_directory_2}")
            os.mkdir(save_directory_2)

        print(" ")
        print("converting...")
        print(" ")
        log = ["path            ,stdev\n"]
        for file_name in os.listdir(directory_name):

            basename = os.path.basename(file_name)
            name = date + "_" + os.path.splitext(basename)[0]

            try:

                data = genfromtxt(directory_name + "/" + file_name, delimiter=',', dtype=None)
                img = data[:, :-1]

                img = img.astype(np.uint8)
                w,h = img.shape
                # mean = cv2.mean(img)[0]
                # print(mean)

                img_to1d = img.flatten()
                stdev = np.std(img_to1d, ddof=1)
                # img_tolist = img_to1d.tolist()
                # print(len(img_tolist))
                # element = set(img_tolist)
                # l = len(element)

                # notice
                if stdev >= 35 or stdev==0:
                    print([name,stdev])
                    log.append(f"{name},{stdev}\n")
                    cv2.imwrite(save_directory + "/" + "notice_img" + "/" + name + ".jpg", img)
                    continue
                else:
                    cv2.imwrite(save_directory + "/" + "normal_img" + "/" + name + ".jpg", img)

            except:
                print([name,"no data"])
                log.append(f"{name},none\n")
                continue

        path = save_directory + "/" + 'notice_log.txt'
        f = open(path, 'w')
        f.writelines(log)
        f.close()

        print(" ")
        print("finish!")
        print(" ")
        ans = input("Do you want to continue (y/n)?")
        if ans == "y" or ans == "Y":
            continue
        else:
            break


