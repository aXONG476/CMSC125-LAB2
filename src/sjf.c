#include <limits.h>

#include "scheduler.h"
#include "metrics.h"
#include "config.h"

void schedule_sjf(Process processes[],
                  int n) {

    int completed = 0;
    int current_time = 0;

    int visited[MAX_PROCESSES] = {0};

    char gantt[MAX_GANTT];
    int gantt_size = 0;

    while (completed < n) {

        int shortest = -1;
        int min_burst = INT_MAX;

        for (int i = 0; i < n; i++) {

            if (!visited[i] &&
                processes[i].arrival_time <= current_time &&
                processes[i].burst_time < min_burst) {

                shortest = i;
                min_burst =
                    processes[i].burst_time;
                }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        visited[shortest] = 1;

        processes[shortest].start_time =
            current_time;

        for (int t = 0;
             t < processes[shortest].burst_time;
             t++) {

            gantt[gantt_size++] =
                processes[shortest].pid[0];

            current_time++;
             }

        processes[shortest].finish_time =
            current_time;

        completed++;
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