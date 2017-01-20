ffmpeg -i /dev/video0 -f image2pipe - 2>/dev/null | ./read-and-view-video.exe --print --verbose | ./read-and-view-video.exe --verbose
