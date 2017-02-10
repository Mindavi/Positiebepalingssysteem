#!/usr/bin/python

import cv2
import ImageReader

escape_key = 27

reader = ImageReader.ImageReader()

fgbg = cv2.createBackgroundSubtractorMOG2()

while True:
    imgread, img = reader.decode()
    if imgread:
        fgmask = fgbg.apply(img)
        cv2.imshow("frame", fgmask)
    key = cv2.waitKey(1) & 0xFF
    if key == escape_key:
        break

cv2.destroyAllWindows()
