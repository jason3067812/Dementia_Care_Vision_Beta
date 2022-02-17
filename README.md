# Dementia-Care-Vision-Beta
 
- This research is still under development and will be published soon.

## Abstract

- Develop a bed exist monitor by PIR camera
- Analyze sleeping quality in computer vision viewpoint

## Progress so far
### 1. Image Prerpocessing
#### a. Magic Eraser

- Purpose: Solving noise pixel caused by PIR camera<br>

- Method:
  - step1: Go through all single pixel
  - step2: Calculate the difference between the current point and the surrounding points
  - step3: If all difference > threshold, let current pixel = all surround pixels’ average

- Results: 

<img src="https://user-images.githubusercontent.com/56544982/147921171-7d7d4cd5-0028-40a6-a597-b28d9fed2fec.png" alt="Cover" width="70%"/>

<img src="https://user-images.githubusercontent.com/56544982/147922056-4afca771-693d-4393-b1d5-3ed6c463ad08.png" alt="Cover" width="70%"/>

### 2. Moving Detection

- Purpose: Making sleeping quality analysis<br>

- Method:
  - Compare "mask image" similarity (SSIM) 
  - Why using mask image? => to remove the factors(brightness and contrast) that will affect SSIM, only remain the pattern structure
  
- Results:

  Mask Image:

<img src="https://user-images.githubusercontent.com/56544982/147926987-02e70bef-9e99-4a9b-83fc-f75a68c9a147.png" alt="Cover" width="60%"/>

   Compare SSIM discrete level of using mak image and raw image (red dots: mask image, blue dots: raw image):

<img src="https://user-images.githubusercontent.com/56544982/147926620-48c2f4e2-40b6-4c28-b4c3-7057c8e08daa.png" alt="Cover" width="60%"/>

  Claculate moving times:

<img src="https://user-images.githubusercontent.com/56544982/147926773-f25537ed-c58e-490a-a0c6-90082427a394.png" alt="Cover" width="60%"/>

  Calculate moving degree:

<img src="https://user-images.githubusercontent.com/56544982/147926796-cc4ed3cb-5b92-4f11-a020-e0e03b5cd778.png" alt="Cover" width="90%"/>


