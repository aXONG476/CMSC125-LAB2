#ifndef CMSC125_LAB2_SCHEDULER_H
#define CMSC125_LAB2_SCHEDULER_H
#include "process.h"

void schedule_fcfs(Process processes[], int n);

void schedule_rr(Process processes[],
                 int n,
                 int quantum);

void schedule_sjf(Process processes[],
                  int n);

void schedule_stcf(Process processes[],
                   int n);

void schedule_mlfq(Process processes[],
                   int n);

void print_metrics(Process processes[],
                   int n);

void print_gantt_chart(char gantt[],
                       int gantt_size);

void compare_algorithms(Process original[],
                        int n);

#endif //CMSC125_LAB2_SCHEDULER_H