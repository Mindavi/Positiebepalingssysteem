ffmpeg -i capture.mkv -b:v 10000k -f image2pipe - 2>/dev/null | ./bg-subtract.exe --verbose | ./read-and-view-video.exe --verbose 
