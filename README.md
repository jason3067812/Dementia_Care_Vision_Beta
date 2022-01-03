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
Method: Compare mask image similarity (SSIM)<br>
Exhibition:

- 1. Mask Image

![image](https://user-images.githubusercontent.com/56544982/147926484-5d0b1587-8b64-4573-a679-9cf2c32b077d.png)

- 2. Compare the discrete level of using mak image and raw image (red: mask, blue: original)

![image](https://user-images.githubusercontent.com/56544982/147926620-48c2f4e2-40b6-4c28-b4c3-7057c8e08daa.png)

- 3. Claculate moving times

![image](https://user-images.githubusercontent.com/56544982/147926773-f25537ed-c58e-490a-a0c6-90082427a394.png)

- 4. Calculate moving degree

![image](https://user-images.githubusercontent.com/56544982/147926796-cc4ed3cb-5b92-4f11-a020-e0e03b5cd778.png)

### 3. Leaving Bed Detection














