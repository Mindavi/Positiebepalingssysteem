#!/usr/bin/python

import cv2

escape_key = 27

capture = cv2.VideoCapture(0)

fgbg = cv2.createBackgroundSubtractorMOG2()

while True:
  ret, frame = capture.read()
  fgmask = fgbg.apply(frame)
  cv2.imshow("frame", fgmask)
  key = cv2.waitKey(30) & 0xFF
  if key == escape_key:
    break

capture.release()
cv2.destroyAllWindows()
