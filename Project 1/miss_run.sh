#!/bin/bash
BASIC_SIZE=1024;
round=0;

# According to https://www.baeldung.com/linux/check-cache-size-l1-l2-l3
lscpu | grep "cache"

echo "cache_misses,cache_load,cache_miss_ratio(%),dTLB_misses,dTLB_load,dTLB_miss_ratio(%),runtime(ms)" >> miss_out.csv
while(($round<=1024))
do
	ARRAY_SIZE=`expr $BASIC_SIZE + $round \* 1024`
	#echo $ARRAY_SIZE
	./miss_measure -l $ARRAY_SIZE >> miss_out.csv
	let "round++"
done
