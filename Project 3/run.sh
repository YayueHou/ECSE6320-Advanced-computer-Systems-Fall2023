#!/bin/bash

# Define experiment parameters
RWMIXREADS="0 50 70 100"
ACCESS_SIZES="4096 16384 32768 131072"
QUEUE_DEPTHS="16 32"
TEST_DURATION="20s"
TEST_DIRECTORY="./tests"
RESULTS_DIRECTORY="./results"

for rwmixread in $RWMIXREADS; do
    for size in $ACCESS_SIZES; do
        for depth in $QUEUE_DEPTHS; do
            fio --name=randwrite --ioengine=libaio --rw=randwrite --bs=$size --numjobs=1 --size=1g --runtime=$TEST_DURATION --time_based --iodepth=$depth --rwmixread=$rwmixread --directory=$TEST_DIRECTORY --output=$RESULTS_DIRECTORY/fio_results_$rwmixread-$size-$depth.txt
        done
    done
done
