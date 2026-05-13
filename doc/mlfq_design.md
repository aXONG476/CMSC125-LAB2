# MLFQ Design Documentation

## Overview

The implemented Multi-Level Feedback Queue (MLFQ) scheduler was designed to balance responsiveness, fairness, and CPU efficiency across different workload types. The scheduler dynamically adjusts process priorities according to observed CPU behavior, allowing short interactive processes to receive faster service while gradually moving CPU-intensive processes into lower-priority queues.

The implementation uses four priority levels with progressively larger execution quantums. Higher-priority queues prioritize responsiveness, while lower-priority queues reduce scheduling overhead for long-running processes.

---

# Queue Structure

| Queue | Scheduling Policy | Quantum          |
| ----- | ----------------- | ---------------- |
| Q0    | Round Robin       | 8                |
| Q1    | Round Robin       | 24               |
| Q2    | Round Robin       | 48               |
| Q3    | FCFS              | Until Completion |

All new processes initially enter Q0, the highest-priority queue.

---

# Design Justification

## Q0 – Interactive Queue

Q0 uses a small quantum of 8 time units to prioritize responsiveness for short and interactive processes. This allows newly arriving processes to receive CPU access quickly and minimizes response time for lightweight tasks.

Interactive workloads typically finish within higher-priority queues before demotion occurs.

---

## Q1 and Q2 – Transitional Queues

Q1 and Q2 use progressively larger quantums:

* Q1 = 24
* Q2 = 48

These queues reduce context-switch overhead while still preserving preemptive behavior. CPU-bound processes gradually migrate downward as they consume more CPU time.

Larger quantums improve throughput for long-running jobs while maintaining reasonable fairness.

---

## Q3 – Background Queue

Q3 uses FCFS scheduling and allows processes to execute until completion. By the time a process reaches Q3, it has already demonstrated CPU-intensive behavior and is therefore treated as a background task.

Using FCFS in the lowest-priority queue minimizes unnecessary preemption and reduces scheduling overhead for long-running workloads.

---

# Allotment Tracking

Each queue also maintains CPU allotments:

| Queue | Allotment |
| ----- | --------- |
| Q0    | 8         |
| Q1    | 24        |
| Q2    | 48        |
| Q3    | Infinite  |

When a process consumes its entire allotment within a queue, it is demoted to the next lower-priority level.

This behavior allows the scheduler to distinguish between:

* short interactive jobs
* long CPU-bound jobs

---

# Priority Boosting

To prevent starvation, the scheduler performs periodic priority boosting every 50 time units.

During a priority boost:

* all unfinished processes return to Q0
* CPU allotment counters reset

This ensures that long-running processes eventually regain access to higher-priority queues and prevents indefinite postponement.

---

# Empirical Testing Results

The MLFQ scheduler was evaluated using several workload categories.

## Interactive Workloads

Interactive workloads consisted primarily of short burst-time processes.

Observed behavior:

* low response times
* rapid completion of short tasks
* minimal waiting time

Interactive workloads produced low response and turnaround times across preemptive schedulers. STCF achieved the best responsiveness due to continuous shortest-remaining-time selection, while MLFQ maintained reasonable responsiveness while preserving fairness and adaptive scheduling behavior.

---

## CPU-Bound Workloads

CPU-bound workloads consisted of long-running processes.

Observed behavior:

* gradual demotion into lower queues
* reduced context-switch overhead
* improved throughput compared to aggressive Round Robin scheduling

Using larger lower-level quantums significantly improved performance compared to smaller quantum configurations.

---

## Mixed Workloads

Mixed workloads combined:

* short interactive processes
* long CPU-intensive processes

Observed behavior:

* interactive jobs completed quickly
* CPU-heavy jobs migrated downward
* periodic boosting prevented starvation

This workload demonstrated the adaptive behavior of the scheduler most effectively.

---

# Comparison with Standard 3-Level MLFQ

Traditional MLFQ implementations commonly use three queues with smaller quantums such as:

* 4
* 8
* FCFS

The implemented design instead uses:

* 8
* 24
* 48
* FCFS

Key differences include:

| Standard 3-Level MLFQ    | Implemented Design               |
| ------------------------ | -------------------------------- |
| smaller quantums         | larger lower-level quantums      |
| more frequent preemption | reduced scheduling overhead      |
| higher responsiveness    | improved CPU-bound throughput    |
| simpler queue hierarchy  | additional FCFS background queue |

The implemented configuration prioritizes balanced workload handling rather than maximizing responsiveness alone.

---

# Tradeoffs

## Advantages

* improved responsiveness for interactive tasks
* adaptive handling of mixed workloads
* starvation prevention through boosting
* reduced overhead for CPU-bound processes
* clear separation between interactive and background behavior

---

## Disadvantages

* more complex than FCFS or RR
* additional bookkeeping for priorities and allotments
* slightly higher turnaround times for some CPU-heavy workloads
* parameter tuning significantly affects performance

---

# Conclusion

Experimental results demonstrated that different scheduling algorithms perform best under different workload conditions. STCF achieved the lowest response times for interactive workloads, while FCFS and SJF performed efficiently for CPU-bound workloads with minimal scheduling overhead. The implemented MLFQ scheduler provided balanced performance across mixed workloads by combining responsiveness, fairness, and adaptive priority management.
