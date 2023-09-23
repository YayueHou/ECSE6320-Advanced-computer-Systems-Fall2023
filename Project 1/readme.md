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

# Conclusion

2) Based on the results of our experimental study, we observe that for a fixed data access granularity of 64B,256B, and 1024B, an increase in the injection delay leads to a decrease in the latency, and the bandwidth decreases accordingly. Moreover, for a fixed data access granularity, an increase in the ratio of write operations leads to a slight increase in latency, but the bandwidth increases when the injection latency is small, while the bandwidth shows a similar pattern when the injection latency is large. These observations lead us to conclude that in memory, the latency of write operations is higher than the latency of read operations.
3) When the injection delay is chosen to be 0, the Bandwith at this point can be approximated as the Throuput, and through our experiments, we can observe that the latency rises gradually as the write ratio rises, while the Throuput shows a tendency of decreasing first and then increasing.

### 
