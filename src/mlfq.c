#include <stdio.h>

#include "scheduler.h"
#include "metrics.h"
#include "config.h"

#define NUM_QUEUES 4

 //Priority boost
static void mlfq_priority_boost(Process processes[],
                                int n,
                                int current_time,
                                int *last_boost,
                                int boost_period) {

    if (current_time - *last_boost >=
        boost_period) {

        for (int i = 0; i < n; i++) {

            if (processes[i].remaining_time > 0) {

                 //Move back to Q0
                processes[i].priority = 0;

                 //Reset allotment usage
                processes[i].time_in_queue = 0;
            }
        }

        *last_boost = current_time;
    }
}

//Priority adjustment / demotion
static void mlfq_adjust_priority(Process *p) {

     //Queue allotments
    int allotments[NUM_QUEUES] = {
        8,      //q0
        24,     //q1
        48,     //q2
        -1      //q3 = fcfs
    };


    //Lowest queue never demotes
    if (p->priority >= 3)
        return;


     //Demote if allotment exceeded
    if (p->time_in_queue >=
        allotments[p->priority]) {

        p->priority++;

        //Reset usage counter
        p->time_in_queue = 0;
    }
}


//Main MLFQ Scheduler
void schedule_mlfq(Process processes[],
                   int n) {

    int completed = 0;

    int current_time = 0;


    //Queue quantum
    int quantums[NUM_QUEUES] = {
        8,      //q0
        24,     //q1
        48,     //q2
        -1      //q3 = fcfs
    };


     // Priority boost settings
    int boost_period = 50;

    int last_boost = 0;

     // Initialize processes
    for (int i = 0; i < n; i++) {

        processes[i].priority = 0;

        processes[i].time_in_queue = 0;
    }

    char gantt[MAX_GANTT];

    int gantt_size = 0;

    while (completed < n) {

        //Periodic priority boost
        mlfq_priority_boost(processes,
                            n,
                            current_time,
                            &last_boost,
                            boost_period);

        int selected = -1;

        //Find highest-priority
        for (int level = 0;
             level < NUM_QUEUES;
             level++) {

            for (int i = 0; i < n; i++) {

                if (processes[i].priority == level &&
                    processes[i].arrival_time <=
                    current_time &&
                    processes[i].remaining_time > 0) {

                    selected = i;

                    break;
                }
            }

            if (selected != -1)
                break;
        }


         // CPU idle
        if (selected == -1) {

            gantt[gantt_size++] = '-';

            current_time++;

            continue;
        }


         // First execution
        if (!processes[selected].started) {

            processes[selected].started = 1;

            processes[selected].start_time =
                current_time;
        }

        //Determine quantum
        int quantum =
            quantums[
                processes[selected].priority
            ];


        if (quantum == -1) {

            quantum =
                processes[selected]
                .remaining_time;
        }

         //Actual runtime
        int run_time = quantum;

        if (processes[selected]
            .remaining_time < quantum) {

            run_time =
                processes[selected]
                .remaining_time;
        }


         //Execute process
        for (int t = 0;
             t < run_time;
             t++) {

            gantt[gantt_size++] =
                processes[selected]
                .pid[0];

            processes[selected]
                .remaining_time--;

            //CPU USage
            processes[selected]
                .time_in_queue++;

            current_time++;
        }

        if (processes[selected]
            .remaining_time == 0) {

            processes[selected]
                .finish_time =
                current_time;

            completed++;
        }

        else {

            mlfq_adjust_priority(
                &processes[selected]
            );
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