#!/usr/bin/env python
# coding: utf-8

import os
import pandas as pd
import shutil

if __name__=="__main__":

    while True:

        csv_path = input("please enter bed data directory：")
        print(" ")
        print("Below press enter represents default")
        image_path = input("please enter camera image directory (default: out_image)：")
        directory_name = input("please enter save file (default: label_image)：")

        if image_path == "":
            image_path = "out_image"
        if directory_name == "":
            directory_name = "label_image"

        label_0_path = directory_name + "/" + "0"
        label_1_path = directory_name + "/" + "1"
        label_2_path = directory_name + "/" + "2"
        label_3_path = directory_name + "/" + "3"
        label_4_path = directory_name + "/" + "4"
        label_5_path = directory_name + "/" + "other"


        if not os.path.isdir(directory_name):
            print("creating output directory: label_image")
            os.mkdir(directory_name)
        if not os.path.exists(label_0_path):
            os.mkdir(label_0_path)
        if not os.path.exists(label_1_path):
            os.mkdir(label_1_path)
        if not os.path.exists(label_2_path):
            os.mkdir(label_2_path)
        if not os.path.exists(label_3_path):
            os.mkdir(label_3_path)
        if not os.path.exists(label_4_path):
            os.mkdir(label_4_path)
        if not os.path.exists(label_5_path):
            os.mkdir(label_5_path)

        print(" ")
        print("classifying...")
        print(" ")

        df = pd.read_csv(csv_path, header=None)
        # df.head()
        # df.columns

        for image_name in os.listdir(image_path):

            source = image_path + "/" + image_name
            basename = image_name.split("_")[1]
            time_name = list(filter(str.isdigit, basename))
            time_name.insert(2, ':')
            time_name.insert(5, ':')
            final_name = "".join(time_name)
            # print(final_name)

            label_filter = (df[0] == final_name)
            result = df.loc[label_filter, 3]
            result = result.tolist()

            if len(result) == 0:
                shutil.move(source, label_5_path)
            else:
                status = int(result[0])
                if status == 0:
                    shutil.move(source, label_0_path)
                elif status == 1:
                    shutil.move(source, label_1_path)
                elif status == 2:
                    shutil.move(source, label_2_path)
                elif status == 3:
                    shutil.move(source, label_3_path)
                elif status == 4:
                    shutil.move(source, label_4_path)

        print(" ")
        print("finish!")
        print(" ")
        ans = input("Do you want to continue (y/n)?")
        if ans == "y" or ans == "Y":
            continue
        else:
            break


