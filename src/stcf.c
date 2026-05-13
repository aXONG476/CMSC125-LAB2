#include <limits.h>

#include "scheduler.h"
#include "metrics.h"
#include "config.h"

void schedule_stcf(Process processes[],
                   int n) {

    int completed = 0;
    int current_time = 0;

    char gantt[MAX_GANTT];
    int gantt_size = 0;

    while (completed < n) {

        int shortest = -1;
        int min_remaining = INT_MAX;

        for (int i = 0; i < n; i++) {

            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_remaining) {

                shortest = i;

                min_remaining =
                    processes[i].remaining_time;
                }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        if (!processes[shortest].started) {

            processes[shortest].started = 1;

            processes[shortest].start_time =
                current_time;
        }

        gantt[gantt_size++] =
            processes[shortest].pid[0];

        processes[shortest].remaining_time--;

        current_time++;

        if (processes[shortest].remaining_time == 0) {

            processes[shortest].finish_time =
                current_time;

            completed++;
        }
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