#!/bin/bash

function usage() {
    echo "Usage: "$0" <v2r|r2v> <input.mp4> <output.raw>"
    exit -1
}

# Check parameters
# First (convertion switch)
if [ -z $1 ]; then
    usage
fi

# Second
if [ -z $2 ]; then
    usage
else
    # Check if input file exists
    if [ -f '$2' ]; then
        echo "error: file `"$2"` does not exist"
        exit 1
    fi
fi

# Third
if [ -z $3 ]; then
    usage
fi

# Set up local variable
input=$2
output=$3

# Check convertion switch
if [ $1 = "v2r" ]; then
    echo "Converting from mp4 to raw video file"
    ffmpeg -i $input -f image2pipe -vcodec rawvideo -pix_fmt rgb24 - >> $output
else
    if [ $1 = "r2v" ]; then
        echo "Converting from raw video to mp4 file"
	      cat $input | ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1280x720 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 $output
    else
      	echo "error: unknown convertion parameter"
        exit 1
    fi
fi
