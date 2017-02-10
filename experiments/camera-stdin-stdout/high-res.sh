ffmpeg -i /dev/video0 -f image2pipe -b:v 10000k - 2>/dev/null | ./read-and-view-with-edit.exe -v
