ffmpeg -i example-videos/example.mp4 -q:v 2 -f image2pipe - | ./read-and-view-video.exe --verbose 
