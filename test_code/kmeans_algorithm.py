
import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

def segmentation(img):
    
    img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    
    # 獲取影像高度、寬度
    rows, cols = img.shape[:]

    # 影像二維畫素轉換為一維
    data = img.reshape((rows * cols, 1))
    data = np.float32(data)

    # 定義中心 (type,max_iter,epsilon)
    criteria = (cv2.TERM_CRITERIA_EPS +
                cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)

    # 設定標籤
    flags = cv2.KMEANS_RANDOM_CENTERS

    # K-Means聚類 聚整合n類
    compactness, labels, centers = cv2.kmeans(data, 2, None, criteria, 10, flags)

    # 生成最終影像
    dst = labels.reshape((img.shape[0], img.shape[1]))

    return dst

