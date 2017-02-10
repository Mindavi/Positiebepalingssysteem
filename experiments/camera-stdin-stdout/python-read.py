#!/usr/bin/python

import ImageReader
import cv2
import numpy as np

escape_key = 27
reader = ImageReader.ImageReader()

while True:
    imgread, img = reader.decode()
    if imgread:
        cv2.imshow("frame", img)
    key = cv2.waitKey(10) & 0xff
    if key == escape_key:
        break
