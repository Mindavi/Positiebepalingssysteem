echo "Type learning rate between 0.0 and 1.0, or -1 for automatic determination"
read learning_rate

echo "Type erosion size, 0 for no erosion"
read erosion_size

echo "Type dilation size, 0 for no dilation"
read dilation_size

echo "Type blur size, 0 for no blur"
read blur_size

echo "Type threshold, from 0 to 255"
read threshold

echo $(date) "erosion:" $erosion_size " dilation:" $dilation_size " blur:" $blur_size" threshold:" $threshold >> log.txt

ffmpeg -i example-videos/example.mp4 -b:v 10000k -f image2pipe - 2>/dev/null | ./read-and-view-video.exe --print --verbose | ./bg-subtract.exe --verbose --learning_rate $learning_rate | ./blur.exe --verbose --blur $blur_size | ./threshold.exe --verbose --threshold $threshold | ./dilate.exe --verbose --dilate $dilation_size | ./erode.exe --verbose --erode $erosion_size | ./read-and-view-video.exe --verbose
