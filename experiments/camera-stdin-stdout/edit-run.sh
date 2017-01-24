ffmpeg -i /dev/video0 -f image2pipe - 2>/dev/null | ./read-and-view-with-edit.exe -v -p | ./read-and-view-with-edit.exe -v
