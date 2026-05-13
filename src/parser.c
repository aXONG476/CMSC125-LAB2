#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"

int load_workload(const char *filename,
                  Process processes[]) {

    FILE *fp = fopen(filename, "r");

    if (!fp) {
        perror("fopen");
        exit(1);
    }

    char line[256];

    int count = 0;

    while (fgets(line,
                 sizeof(line),
                 fp)) {

        if (line[0] == '#')
            continue;

        if (strlen(line) <= 1)
            continue;

        Process p;

        sscanf(line,
               "%s %d %d",
               p.pid,
               &p.arrival_time,
               &p.burst_time);

        p.remaining_time =
            p.burst_time;

        p.priority = 0;

        p.start_time = -1;
        p.finish_time = 0;

        p.turnaround_time = 0;
        p.waiting_time = 0;
        p.response_time = 0;

        p.started = 0;

        processes[count++] = p;
                 }

    fclose(fp);

    return count;
}