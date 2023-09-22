#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/perf_event.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <time.h>
#include <sys/syscall.h>

#define MUL_TIMES 1000
#define DEBUG 0
#if 1
// wrap perf event
static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags) {
    return syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
}

int main(int argc, char *argv[]) {

    // Set the size of test array
    int ARRAY_SIZE;
    if(strcmp("-l", argv[1]) == 0)
    {
       ARRAY_SIZE = atoi(argv[2]);
    }

    srand((unsigned)time(0));

    // generate test array
	int test_array[ARRAY_SIZE];

	int i=0;
	for(i=0;i<(ARRAY_SIZE);i++)
	{
		test_array[i]=2;

	}
    //printf("The size of the test_array is %dk\n",ARRAY_SIZE/1024*sizeof(int));
	int index1,index2;
	int mul=0;

    // According to OpenAI. (2023). ChatGPT (Feb 13 version) [Large language model]. https://chat.openai.com
    // The answer of "how to measure the cache miss ratio and dTLB miss ratio using perf_event"

    // Define perf event of cache miss and cache hint  
    struct perf_event_attr pe_cache_hits, pe_cache_misses;
    int fd_cache_hits, fd_cache_misses;
    uint64_t count_hits, count_misses;

    // Define perf event of dTLB miss and dTLB hint
    struct perf_event_attr pe_dtlb_loads, pe_dtlb_load_misses;
    int fd_dtlb_loads, fd_dtlb_load_misses;
    uint64_t count_dtlb_loads, count_dtlb_load_misses;

    // Initialize the perf event  for cache miss and cache hint
    memset(&pe_cache_hits, 0, sizeof(struct perf_event_attr));
    pe_cache_hits.type = PERF_TYPE_HW_CACHE;
    pe_cache_hits.size = sizeof(struct perf_event_attr);
    pe_cache_hits.config = (PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16));

    memset(&pe_cache_misses, 0, sizeof(struct perf_event_attr));
    pe_cache_misses.type = PERF_TYPE_HW_CACHE;
    pe_cache_misses.size = sizeof(struct perf_event_attr);
    pe_cache_misses.config = (PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16));

    // Initialize the perf event for dTLB miss and dTLB hint
    memset(&pe_dtlb_loads, 0, sizeof(struct perf_event_attr));
    pe_dtlb_loads.type = PERF_TYPE_HW_CACHE;
    pe_dtlb_loads.size = sizeof(struct perf_event_attr);
    pe_dtlb_loads.config = (PERF_COUNT_HW_CACHE_DTLB << 0  | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16));

    memset(&pe_dtlb_load_misses, 0, sizeof(struct perf_event_attr));
    pe_dtlb_load_misses.type = PERF_TYPE_HW_CACHE;
    pe_dtlb_load_misses.size = sizeof(struct perf_event_attr);
    pe_dtlb_load_misses.config = (PERF_COUNT_HW_CACHE_DTLB << 0  | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16));

    // Create perf events for cache hits and misses
    fd_cache_hits = perf_event_open(&pe_cache_hits, 0, -1, -1, 0);
    fd_cache_misses = perf_event_open(&pe_cache_misses, 0, -1, -1, 0);

    // Create perf events for dTLB loads and dTLB load misses
    fd_dtlb_loads = perf_event_open(&pe_dtlb_loads, 0, -1, -1, 0);
    fd_dtlb_load_misses = perf_event_open(&pe_dtlb_load_misses, 0, -1, -1, 0);


    if (fd_cache_hits == -1 || fd_cache_misses == -1 || fd_dtlb_loads == -1 || fd_dtlb_load_misses == -1) {
        perror("Error opening perf events");
        exit(EXIT_FAILURE);
    }
 
    // Start measuring
    ioctl(fd_cache_hits, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd_cache_hits, PERF_EVENT_IOC_ENABLE, 0);

    ioctl(fd_cache_misses, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd_cache_misses, PERF_EVENT_IOC_ENABLE, 0);

    ioctl(fd_dtlb_loads, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd_dtlb_loads, PERF_EVENT_IOC_ENABLE, 0);

    ioctl(fd_dtlb_load_misses, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd_dtlb_load_misses, PERF_EVENT_IOC_ENABLE, 0);

    // start time calculate
    clock_t begin = clock();

    // the multiplication to measure
    for(i=0;i<(MUL_TIMES);i++)
	{
	    index1=rand()%(ARRAY_SIZE);
	    index2=rand()%(ARRAY_SIZE);
	    mul=test_array[index1]*test_array[index2];
	}

    // end time calculate
    clock_t end = clock();

    // Stop measuring
    ioctl(fd_cache_hits, PERF_EVENT_IOC_DISABLE, 0);
    ioctl(fd_cache_misses, PERF_EVENT_IOC_DISABLE, 0);

    read(fd_cache_hits, &count_hits, sizeof(uint64_t));
    read(fd_cache_misses, &count_misses, sizeof(uint64_t));

    ioctl(fd_dtlb_loads, PERF_EVENT_IOC_DISABLE, 0);
    ioctl(fd_dtlb_load_misses, PERF_EVENT_IOC_DISABLE, 0);

    read(fd_dtlb_loads, &count_dtlb_loads, sizeof(uint64_t));
    read(fd_dtlb_load_misses, &count_dtlb_load_misses, sizeof(uint64_t));

    // Close the perf events
    close(fd_cache_hits);
    close(fd_cache_misses);

    close(fd_dtlb_loads);
    close(fd_dtlb_load_misses);



    // Calculate the cache miss ratio
    double miss_ratio = (double)count_misses / (double)(count_hits + count_misses);
    double dtlb_miss_ratio = (double)count_dtlb_load_misses / (double)(count_dtlb_loads + count_dtlb_load_misses);

    double time_spent = (double)(end - begin)/CLOCKS_PER_SEC*1000; // ms

    if(DEBUG)
    {
        printf("Cache Miss Ratio: %.2f%%\n", miss_ratio * 100.0);
        printf("dTLB Miss Ratio: %.2f%%\n", dtlb_miss_ratio * 100.0);
        printf("runtime:%fms\n",time_spent);
    }

    printf("%f %f %.2f%% %f %f %.2f%% %f\n",
            (double)count_misses, (double)(count_hits + count_misses), miss_ratio* 100.0, 
            (double)count_dtlb_load_misses,(double)(count_dtlb_loads + count_dtlb_load_misses), dtlb_miss_ratio* 100.0,
            time_spent);

    return 0;
}

#endif

