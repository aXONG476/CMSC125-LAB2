#include <stdio.h>

#include "process.h"
#include "metrics.h"

void calculate_metrics(Process processes[],
                       int n) {

    for (int i = 0; i < n; i++) {

        processes[i].turnaround_time =
            processes[i].finish_time -
            processes[i].arrival_time;

        processes[i].waiting_time =
            processes[i].turnaround_time -
            processes[i].burst_time;

        processes[i].response_time =
            processes[i].start_time -
            processes[i].arrival_time;
    }
}

void print_metrics(Process processes[],
                   int n) {

    double avg_tt = 0;
    double avg_wt = 0;
    double avg_rt = 0;

    printf("\n=== Metrics ===\n\n");

    printf("Process | AT  | BT  | FT  | TT  | WT  | RT\n");
    printf("--------|-----|-----|-----|-----|-----|-----\n");

    for (int i = 0; i < n; i++) {

        printf("%-7s | %3d | %3d | %3d | %3d | %3d | %3d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].finish_time,
               processes[i].turnaround_time,
               processes[i].waiting_time,
               processes[i].response_time);

        avg_tt += processes[i].turnaround_time;
        avg_wt += processes[i].waiting_time;
        avg_rt += processes[i].response_time;
    }

    avg_tt /= n;
    avg_wt /= n;
    avg_rt /= n;

    printf("--------|-----|-----|-----|-----|-----|-----\n");

    printf("Average |     |     |     | %.0f | %.0f | %.0f\n",
           avg_tt,
           avg_wt,
           avg_rt);

    // Convoy effect detection
    for (int i = 0; i < n; i++) {

        if (processes[i].waiting_time > 200) {

            printf("\nConvoy effect detected: ");

            printf("Process %s waited %d time units\n",
                   processes[i].pid,
                   processes[i].waiting_time);

            break;
        }
    }
}