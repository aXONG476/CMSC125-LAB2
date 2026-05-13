#include "scheduler.h"
#include "metrics.h"
#include "config.h"

void schedule_fcfs(Process processes[],
                   int n) {

    int current_time = 0;

    char gantt[MAX_GANTT];
    int gantt_size = 0;

    for (int i = 0; i < n; i++) {

        if (current_time <
            processes[i].arrival_time) {

            current_time =
                processes[i].arrival_time;
            }

        processes[i].start_time =
            current_time;

        for (int t = 0;
             t < processes[i].burst_time;
             t++) {

            gantt[gantt_size++] =
                processes[i].pid[0];

            current_time++;
             }

        processes[i].finish_time =
            current_time;
    }

    calculate_metrics(processes,
                      n);

    if (!silent_mode) {

        print_gantt_chart(gantt,
                          gantt_size);

        print_metrics(processes,
                      n);
    }
}