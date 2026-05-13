#include "scheduler.h"
#include "metrics.h"
#include "config.h"

void schedule_rr(Process processes[],
                 int n,
                 int quantum) {

    int completed = 0;
    int current_time = 0;

    char gantt[MAX_GANTT];
    int gantt_size = 0;

    while (completed < n) {

        int found = 0;

        for (int i = 0; i < n; i++) {

            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0) {

                found = 1;

                if (!processes[i].started) {

                    processes[i].started = 1;

                    processes[i].start_time =
                        current_time;
                }

                int run_time = quantum;

                if (processes[i].remaining_time <
                    quantum) {

                    run_time =
                        processes[i].remaining_time;
                    }

                for (int t = 0;
                     t < run_time;
                     t++) {

                    gantt[gantt_size++] =
                        processes[i].pid[0];

                    processes[i].remaining_time--;

                    current_time++;
                     }

                if (processes[i].remaining_time == 0) {

                    processes[i].finish_time =
                        current_time;

                    completed++;
                }
                }
        }

        if (!found)
            current_time++;
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