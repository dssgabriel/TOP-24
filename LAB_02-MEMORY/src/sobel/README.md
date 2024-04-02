# Sobel filter

## About

This code applies a sobel filter on a video stream.
It processes the video frame by frame and writes the new frame straight to the disk drive.

## Build

```sh
make
```

## Run
First, you need to convert the input video into the raw RGB format using the following script (make sure `ffmpeg` is installed on your Linux distribution):
```sh
./cvt_vid.sh v2r in/input.mp4 in/input.raw
```
Then you can run the program as follows:
```sh
./build/sobel input/input.raw output/output.raw
```

Once the program is done, you can check the output video by converting it from the raw format to mp4 using the provided script as follows:
```sh
./cvt_vid.sh r2v output/output.raw output/output.mp4
```

After the convertion is finished, you can play the video to verify is the output is valid using `vlc`:
```sh
vlc output/output.mp4 
```

## Output
The program output the frame id, the size of the frame, the run time in ns and the bandwidth in MiB/s.
Then, it prints simple stat: min, max, average bandwidth and the standard deviation of the collected samples.
```
     .
     .
     .
    358;              5529600 bytes;    47927046.000 ns;         110.031 MiB/s
    359;              5529600 bytes;    47966936.000 ns;         109.939 MiB/s

5529600 bytes;    47454050.000 ns;    55694524.000 ns;    47954474.858 ns;         109.968 MiB/s;           1.662 %;
```
