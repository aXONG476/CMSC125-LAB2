#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "process.h"
#include "scheduler.h"

int load_workload(const char *filename,
                  Process processes[]);

int main(int argc,
         char *argv[]) {

    int compare_mode = 0;

    char algorithm[32] = "";
    char input_file[128] = "";

    int quantum = 2;

    // Parse arguments
    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i],
                   "--algorithm") == 0 &&
            i + 1 < argc) {

            strcpy(algorithm,
                   argv[i + 1]);
        }

        else if (strcmp(argv[i],
                        "--input") == 0 &&
                 i + 1 < argc) {

            strcpy(input_file,
                   argv[i + 1]);
        }

        else if (strcmp(argv[i],
                        "--quantum") == 0 &&
                 i + 1 < argc) {

            quantum =
                atoi(argv[i + 1]);
        }

        else if (strcmp(argv[i],
                        "--compare") == 0) {

            compare_mode = 1;
        }
    }

    // Validate input file
    if (strlen(input_file) == 0) {

        printf("Error: Missing input file\n");

        return 1;
    }

    Process processes[MAX_PROCESSES];

    int n =
        load_workload(input_file,
                      processes);

    // Compare mode
    if (compare_mode) {

        compare_algorithms(processes,
                           n);

        return 0;
    }

    // Normal scheduling mode
    if (strcmp(algorithm,
               "FCFS") == 0) {

        schedule_fcfs(processes,
                      n);
    }

    else if (strcmp(algorithm,
                    "RR") == 0) {

        schedule_rr(processes,
                    n,
                    quantum);
    }

    else if (strcmp(algorithm,
                    "SJF") == 0) {

        schedule_sjf(processes,
                     n);
    }

    else if (strcmp(algorithm,
                    "STCF") == 0) {

        schedule_stcf(processes,
                      n);
    }

    else if (strcmp(algorithm,
                    "MLFQ") == 0) {

        schedule_mlfq(processes,
                      n);
    }

    else {

        printf("Unknown or missing algorithm\n");

        printf("\nUsage:\n");

        printf("./schedsim --algorithm FCFS --input workload.txt\n");

        printf("./schedsim --compare --input workload.txt\n");

        return 1;
    }

    return 0;
}