# Cache and Memory Performance Profiling
## (1) The read/write latency of cache and main memory when the queue length is zero (i.e., zero queuing delay)



## (2) The maximum bandwidth of the main memory under different data access granularity (i.e., 64B, 256B, 1024B) and different read vs. write intensity ratio (i.e., read-only, write-only, 70:30 ratio, 50:50 ratio)
![](./figures/64Bytes.png)
![](./figures/256Bytes.png)
![](./figures/1024Bytes.png)


## (3) The trade-off between read/write latency and throughput of the main memory to demonstrate what the queuing theory predicts
![](./figures/Trade-off64.png)
![](./figures/Tradeoff256.png)
![](./figures/Tradeoff1024.png)




## (4) The impact of cache miss ratio on the software speed performance (the software is supposed to execute relatively light computations such as multiplication)
## (5) The impact of TLB table miss ratio on the software speed performance (again, the software is supposed to execute relatively light computations such as multiplication)
