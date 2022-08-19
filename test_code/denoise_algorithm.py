

import cv2
import numpy as np
import matplotlib.pyplot as plt
import os
from collections import OrderedDict

def denoise(gray_img,pixel):
    
        
    img_copy = gray_img
    shape = gray_img.shape
    ymax = shape[0]
    xmax = shape[1]

    for i in range(ymax):

        for j in range(xmax):
            adjacent_list = []

            now_pixel = gray_img[i][j]
            #print(f"點{(i,j)}的值:{now_pixel}")

            # 順序:上下左右       
            # 向上搜索
            if j-1 >= 0:
                up_pixel = gray_img[i][j-1]
                adjacent_list.append(up_pixel)            

            # 向下搜索
            if j+1 < xmax:
                down_pixel = gray_img[i][j+1]
                adjacent_list.append(down_pixel)

            # 向左搜索
            if i-1 >= 0:
                left_pixel = gray_img[i-1][j]
                adjacent_list.append(left_pixel)

            # 向右搜索
            if i+1 < ymax:
                right_pixel = gray_img[i+1][j]
                adjacent_list.append(right_pixel)


            final_list = list(OrderedDict.fromkeys(adjacent_list))

            if len(final_list) == 1 and final_list[0] == pixel:
                img_copy[i][j] = pixel
    
    return img_copy
    
    

