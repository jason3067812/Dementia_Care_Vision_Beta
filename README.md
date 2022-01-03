# Dementia-Care-Vision-Beta
 
This research is still under development and will be published soon

## Abstract

- Develop a bed exist monitor by PIR camera
- Analyze sleeping quality in computer vision viewpoint

## Recently Progress

### 1. Magic Eraser
Purpose: Solving noise pixel caused by PIR camera<br>
Method: 
- step1: Go through all single pixel
- step2: Calculate the difference between the current point and the surrounding points
- step3: If all difference > threshold, let current pixel = all surround pixels’ average


Exhibition: 

![image](https://user-images.githubusercontent.com/56544982/147921171-7d7d4cd5-0028-40a6-a597-b28d9fed2fec.png)

![image](https://user-images.githubusercontent.com/56544982/147922056-4afca771-693d-4393-b1d5-3ed6c463ad08.png)


### 2. Moving Detection
Purpose: Making sleeping quality analysis<br>
Problem: SSIM is easily influenced by heat noise bc it considers brightness and contrast<br>
Method: Compare image similarity (SSIM)






