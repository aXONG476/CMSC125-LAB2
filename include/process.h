#ifndef CMSC125_LAB2_PROCESS_H
#define CMSC125_LAB2_PROCESS_H

#define MAX_PROCESSES 100
#define MAX_GANTT 1000

typedef struct {

    char pid[16];

    int arrival_time;

    int burst_time;

    int remaining_time;

    int priority;

    int start_time;

    int finish_time;

    int turnaround_time;

    int waiting_time;

    int response_time;

    int started;

    int context_switches;

    int time_in_queue;

} Process;

#endif