dilate_size=20
erode_size=4

blur_size=10
blob_size=2000

ffmpeg -i example-videos/example.mp4 -q:v 31 -f image2pipe - | ./bg-subtract.exe  | ./blur.exe --blur $blur_size | ./erode.exe --erode $erode_size | ./dilate.exe --dilate $dilate_size | ./threshold.exe --threshold 200 | ./blob-detect.exe --min_area $blob_size | ffmpeg -i - -f image2 -r 24 -f mp4 out.mp4
