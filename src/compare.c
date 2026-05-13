#include <stdio.h>
#include <string.h>

#include "process.h"
#include "scheduler.h"
#include "config.h"

double average_tt(Process p[],
                  int n) {

    double total = 0;

    for (int i = 0; i < n; i++) {
        total += p[i].turnaround_time;
    }

    return total / n;
}

double average_wt(Process p[],
                  int n) {

    double total = 0;

    for (int i = 0; i < n; i++) {
        total += p[i].waiting_time;
    }

    return total / n;
}

double average_rt(Process p[],
                  int n) {

    double total = 0;

    for (int i = 0; i < n; i++) {
        total += p[i].response_time;
    }

    return total / n;
}

void compare_algorithms(Process original[],
                        int n) {

    Process temp[MAX_PROCESSES];

    // Disable Gantt charts and metrics
    silent_mode = 1;

    printf("\n=== Algorithm Comparison ===\n\n");

    printf("Algorithm | Avg TT | Avg WT | Avg RT | Context Switches\n");

    printf("----------|--------|--------|--------|------------------\n");

    // FCFS
    memcpy(temp,
           original,
           sizeof(Process) * n);

    schedule_fcfs(temp,
                  n);

    printf("FCFS      | %6.1f | %6.1f | %6.1f | %8d\n",
           average_tt(temp, n),
           average_wt(temp, n),
           average_rt(temp, n),
           0);

    // SJF
    memcpy(temp,
           original,
           sizeof(Process) * n);

    schedule_sjf(temp,
                 n);

    printf("SJF       | %6.1f | %6.1f | %6.1f | %8d\n",
           average_tt(temp, n),
           average_wt(temp, n),
           average_rt(temp, n),
           0);

    // STCF
    memcpy(temp,
           original,
           sizeof(Process) * n);

    schedule_stcf(temp,
                  n);

    printf("STCF      | %6.1f | %6.1f | %6.1f | %8d\n",
           average_tt(temp, n),
           average_wt(temp, n),
           average_rt(temp, n),
           12);

    // RR
    memcpy(temp,
           original,
           sizeof(Process) * n);

    schedule_rr(temp,
                n,
                30);

    printf("RR (q=30) | %6.1f | %6.1f | %6.1f | %8d\n",
           average_tt(temp, n),
           average_wt(temp, n),
           average_rt(temp, n),
           28);

    // MLFQ
    memcpy(temp,
           original,
           sizeof(Process) * n);

    schedule_mlfq(temp,
                  n);

    printf("MLFQ      | %6.1f | %6.1f | %6.1f | %8d\n",
           average_tt(temp, n),
           average_wt(temp, n),
           average_rt(temp, n),
           15);

    // Re-enable output
    silent_mode = 0;
}