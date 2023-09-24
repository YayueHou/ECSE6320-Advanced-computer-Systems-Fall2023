#!/bin/bash
MLC="./mlc"
RESULTS="./results"
MLC_OUTPUT="mlc_output.txt"
ACCESS_SIZES="64 256 1024"
READ_WRITE_RATIO="6 7 8 9"

# 1)
#sudo $MLC --idle_latency >$RESULTS/mlc_zero-queue.txt
#sudo $MLC --idle_latency >$RESULTS/mlc_zero-queue-R.txt

# 2) and 3)
for option in $READ_WRITE_RATIO; do
    for access_size in $ACCESS_SIZES; do
        # sudo $MLC --loaded_latency -W$option -l$access_size > $RESULTS/mlc_test_$access_size-W-$option.txt
        # sudo $MLC --loaded_latency -R -l$access_size > $RESULTS/mlc_text_$access_size-R.txt
        sudo $MLC --loaded_latency -W$option -l$access_size -d0 >$RESULTS/mlc_throughput_$access_size-W-$option.txt
        sudo $MLC --loaded_latency -R  -l$access_size -d0 >$RESULTS/mlc_throughput_$access_size-R.txt
    done
done


