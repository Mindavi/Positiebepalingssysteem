ffmpeg -i example-videos/example.mp4 -b:v 10000k -f image2pipe - 2>/dev/null | ./read-and-view-video.exe --verbose 
