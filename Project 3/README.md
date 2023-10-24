## SSD Performance Profiling
This is the Project 3 in Advanced-Computer-Systems-Fall2023.
### Instructions
This project helps to gain first-hands experience on profiling the performance of modern SSDs.

FIO is a storage device testing tool widely used in the
industry. Like Project 1, we should design a set of experiments to measure the SSD performance (latency and
throughput) under different combinations of the following parameters: 

1) data access size (e.g.,4KB/16KB/32KB/128KB)

2) read vs. write intensity ratio (e.g., read-only, write-only, 50%:50% and 70%:30% read vs. write)

3)  I/O queue depth (e.g., 0~1024)

### Quick Start
```
sh run.sh
```
### Results

IO Depth = 16

| Test Type          | Block Size | IOPS  | Bandwidth Read/Write | Latency min (usec) | Latency max (usec) | Latency avg (usec) | Bandwidth avg (KiB/s) | CPU usr | CPU sys | IO Depth  |
|--------------------|------------|-------|----------------------|--------------------|--------------------|--------------------|-----------------------|---------|---------|-----------|
| 100% write         | 4 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 16        |
| 100% write         | 16 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 16        |
| 100% write         | 32 KiB     | 22.2k | 727MB/s (693MiB/s)   | 24                 | 853052             | 693.74             | 826118.7              | 4.58%   | 70.72%  | 16        |
| 100% write         | 128 KiB    | 5513  | 723MB/s (689MiB/s)   | 148                | 810232             | 2747.13            | 946727.23             | 2.00%   | 70.08%  | 16        |
| 50% read 50% write | 4 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 16        |
| 50% read 50% write | 16 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 16        |
| 50% read 50% write | 32 KiB     | 22.2k | 727MB/s (693MiB/s)   | 24                 | 853052             | 693.74             | 826118.7              | 4.58%   | 70.72%  | 16        |
| 50% read 50% write | 128 KiB    | 5513  | 723MB/s (689MiB/s)   | 148                | 810232             | 2747.13            | 946727.23             | 2.00%   | 70.08%  | 16        |
| 70% read 30% write | 4 KiB      | 134k  | 525 MiB/s (550 MB/s) | 2                  | 895291             | 115.8              | 566794.38             | 17.28%  | 63.16%  | 16        |
| 70% read 30% write | 16 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 16        |
| 70% read 30% write | 32 KiB     | 22.3k | 698 MiB/s (731 MB/s) | 24                 | 821068             | 686.34             | 909065.2              | 5.08%   | 70.76%  | 16        |
| 70% read 30% write | 128 KiB    | 5697  | 712MiB/s (747MB/s)   | 72                 | 815279             | 2649.41            | 811571.18             | 2.39%   | 70.30%  | 16        |
| 100% read          | 4 KiB      | 128k  | 500MiB/s (524MB/s)   | 10                 | 851138             | 117.28             | 158843.52             | 16.44%  | 63.53%  | 16        |
| 100% read          | 16 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 16        |
| 100% read          | 32 KiB     | 22.1k | 690MiB/s (724MB/s)   | 7                  | 837,672            | 700                | 838,709.11            | 4.28%   | 69.83%  | 16        |
| 100% read          | 128 KiB    | 5610  | 701MiB/s (735MB/s)   | 53                 | 816744             | 2753.63            | 917293.97             | 1.88%   | 70.66%  | 16        |

IO Depth = 32

| Test Type          | Block Size | IOPS  | Bandwidth Read/Write | Latency min (usec) | Latency max (usec) | Latency avg (usec) | Bandwidth avg (KiB/s) | CPU usr | CPU sys | IO Depth  |
|--------------------|------------|-------|----------------------|--------------------|--------------------|--------------------|-----------------------|---------|---------|-----------|
| 100% write         | 4 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 32        |
| 100% write         | 16 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 32        |
| 100% write         | 32 KiB     | 22.2k | 727MB/s (693MiB/s)   | 24                 | 853052             | 693.74             | 826118.7              | 4.58%   | 70.72%  | 32        |
| 100% write         | 128 KiB    | 5513  | 723MB/s (689MiB/s)   | 148                | 810232             | 2747.13            | 946727.23             | 2.00%   | 70.08%  | 32        |
| 50% read 50% write | 4 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 32        |
| 50% read 50% write | 16 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 32        |
| 50% read 50% write | 32 KiB     | 22.2k | 727MB/s (693MiB/s)   | 24                 | 853052             | 693.74             | 826118.7              | 4.58%   | 70.72%  | 32        |
| 50% read 50% write | 128 KiB    | 5513  | 723MB/s (689MiB/s)   | 148                | 810232             | 2747.13            | 946727.23             | 2.00%   | 70.08%  | 32        |
| 70% read 30% write | 4 KiB      | 134k  | 525 MiB/s (550 MB/s) | 2                  | 895291             | 115.8              | 566794.38             | 17.28%  | 63.16%  | 32        |
| 70% read 30% write | 16 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 32        |
| 70% read 30% write | 32 KiB     | 22.3k | 698 MiB/s (731 MB/s) | 24                 | 821068             | 686.34             | 909065.2              | 5.08%   | 70.76%  | 32        |
| 70% read 30% write | 128 KiB    | 5697  | 712MiB/s (747MB/s)   | 72                 | 815279             | 2649.41            | 811571.18             | 2.39%   | 70.30%  | 32        |
| 100% read          | 4 KiB      | 128k  | 500MiB/s (524MB/s)   | 10                 | 851138             | 117.28             | 158843.52             | 16.44%  | 63.53%  | 32        |
| 100% read          | 16 KiB      | 133k  | 543MB/s (518MiB/s)   | 5                  | 828546             | 116.92             | 599177.8              | 16.12%  | 64.15%  | 32        |
| 100% read          | 32 KiB     | 22.1k | 690MiB/s (724MB/s)   | 7                  | 837,672            | 700                | 838,709.11            | 4.28%   | 69.83%  | 32        |
| 100% read          | 128 KiB    | 5610  | 701MiB/s (735MB/s)   | 53                 | 816744             | 2753.63            | 917293.97             | 1.88%   | 70.66%  | 32        |


