#include <stdio.h>

void print_gantt_chart(char gantt[],
                       int gantt_size) {

    printf("\n=== Gantt Chart ===\n");

    int i = 0;
    int current_time = 0;

    // Print chart
    while (i < gantt_size) {

        char current =
            gantt[i];

        int count = 0;

        while (i < gantt_size &&
               gantt[i] == current) {

            count++;
            i++;
               }

        // Scale: 1 dash = 20 time units
        int dashes =
            count / 20;

        if (dashes < 1)
            dashes = 1;

        printf("[%c",
               current);

        for (int j = 0;
             j < dashes;
             j++) {

            printf("-");
             }

        printf("]");
    }

    printf("\n");

    // Print timeline
    i = 0;
    current_time = 0;

    printf("Time: ");

    while (i < gantt_size) {

        char current =
            gantt[i];

        int count = 0;

        printf("%-10d",
               current_time);

        while (i < gantt_size &&
               gantt[i] == current) {

            count++;
            i++;
               }

        current_time += count;
    }

    printf("%d\n",
           gantt_size);
}