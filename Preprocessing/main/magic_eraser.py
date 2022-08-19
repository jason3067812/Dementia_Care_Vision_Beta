#!/usr/bin/env python
# coding: utf-8

import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

if __name__=="__main__":

    while True:

        print(" ")
        directory_name = input("please enter image path:")
        print(" ")
        new_directory_name = input("please enter save file:")
        print(" ")
        print("Below press enter represents default")
        threshold = input("please enter erase intensity (default: 15):")
        if threshold == "":
            threshold = 15


        for filename in os.listdir(directory_name):

            # 讀取原始影像灰度顏色
            img = cv2.imread(directory_name + "/" + filename,0)

            img_copy = img
            shape = img.shape
            ymax = shape[0]
            xmax = shape[1]

            for i in range(ymax):
                for j in range(xmax):
                    count = 0
                    adjacent_list = []

                    now_pixel = int(img[i][j])

                    if j-1 >= 0:
                        count+=1
                        up_pixel = int(img[i][j-1])

                        if abs(up_pixel - now_pixel) > threshold:
                            adjacent_list.append(up_pixel)


                    if j+1 < xmax:
                        count+=1
                        down_pixel = int(img[i][j+1])

                        if abs(down_pixel - now_pixel) > threshold:
                            adjacent_list.append(down_pixel)


                    if i-1 >= 0:
                        count+=1
                        left_pixel = int(img[i-1][j])

                        if abs(left_pixel - now_pixel) > threshold:
                            adjacent_list.append(left_pixel)


                    if i+1 < ymax:
                        count+=1
                        right_pixel = int(img[i+1][j])

                        if abs(right_pixel - now_pixel) > threshold:
                            adjacent_list.append(right_pixel)

                    if count == len(adjacent_list):

                        average = int(sum(adjacent_list)/count)
                        img_copy[i][j] = average

                        #print(f"pixel{(i,j)}:{now_pixel} => {average}")

            cv2.imwrite(new_directory_name + "/" + filename, img_copy)

        print("finish")
        print(" ")
        ans = input("Do you want to continue (y/n)?")
        if ans == "y" or ans == "Y":
            continue
        else:
            break




