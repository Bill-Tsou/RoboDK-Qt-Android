import cv2
import numpy as np
import sys

if len(sys.argv) < 2:
	print("Not enough parameter!")
	exit(0)

Result1="Mask"
Result="Cam Result"
input_image = 'cam_shot.png'

img = cv2.imread(input_image)

blue_lower = np.array([250, 0, 0])
blue_upper = np.array([255, 255, 255])

green_lower = np.array([0, 250, 0])
green_upper = np.array([255, 255, 255])

red_lower = np.array([0, 0, 250])
red_upper = np.array([255, 255, 255])

mask_blue = cv2.inRange(img, blue_lower, blue_upper)
contours, hier = cv2.findContours(mask_blue.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
for cont in contours:
	area = cv2.contourArea(cont)
	if area < 500:
		continue

	if sys.argv[1] == "show_window":
		seg_img = cv2.bitwise_and(img, img, mask=mask_blue)
		output = cv2.drawContours(seg_img, contours, -1, (120, 120, 120), 3)
		text = 'Blue'
		cv2.putText(output,text,(0,50),cv2.FONT_HERSHEY_SIMPLEX,2,(255,0,0),3,cv2.LINE_AA)
		cv2.namedWindow(Result1)
		cv2.imshow(Result1, mask_blue)
		cv2.moveWindow(Result1, 500,0)
		cv2.namedWindow(Result)
		cv2.imshow(Result, output)
		cv2.moveWindow(Result, 1000,0)
		break
	else:
		print("Blue", end="")
		exit(0)

mask_green = cv2.inRange(img, green_lower, green_upper)
contours, hier = cv2.findContours(mask_green.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
for cont in contours:
	area = cv2.contourArea(cont)
	if area < 500:
		continue
	if sys.argv[1] == "show_window":
		seg_img = cv2.bitwise_and(img, img, mask=mask_green)
		output = cv2.drawContours(seg_img, contours, -1, (120, 120, 120), 3)
		text = 'Green'
		cv2.putText(output,text,(0,50),cv2.FONT_HERSHEY_SIMPLEX,2,(0,255,0),3,cv2.LINE_AA)
		cv2.namedWindow(Result1)
		cv2.imshow(Result1, mask_green)
		cv2.moveWindow(Result1, 500,0)
		cv2.namedWindow(Result)
		cv2.imshow(Result, output)
		cv2.moveWindow(Result, 1000,0)
		break
	else:
		print("Green", end="")
		exit(0)

mask_red = cv2.inRange(img, red_lower, red_upper)
contours, hier = cv2.findContours(mask_red.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
for cont in contours:
	area = cv2.contourArea(cont)
	if area < 500:
		continue

	if sys.argv[1] == "show_window":
		seg_img = cv2.bitwise_and(img, img, mask=mask_red)
		output = cv2.drawContours(seg_img, contours, -1, (120, 120, 120), 3)
		text = 'Red'
		cv2.putText(output,text,(0,50),cv2.FONT_HERSHEY_SIMPLEX,2,(0,0,255),3,cv2.LINE_AA)
		cv2.namedWindow(Result1)
		cv2.imshow(Result1, mask_red)
		cv2.moveWindow(Result1, 500,0)
		cv2.namedWindow(Result)
		cv2.imshow(Result, output)
		cv2.moveWindow(Result, 1000,0)
		cv2.setWindowProperty(Result1,cv2.WND_PROP_FULLSCREEN,cv2.WINDOW_FULLSCREEN)
		cv2.setWindowProperty(Result1,cv2.WND_PROP_FULLSCREEN,cv2.WINDOW_NORMAL)

		cv2.setWindowProperty(Result,cv2.WND_PROP_FULLSCREEN,cv2.WINDOW_FULLSCREEN)
		cv2.setWindowProperty(Result,cv2.WND_PROP_FULLSCREEN,cv2.WINDOW_NORMAL)
		break
	else:
		print("Red", end="")
		exit(0)

cv2.waitKey(0)
cv2.destroyAllWindows()
