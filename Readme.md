# CMSC 125 Lab 2 – CPU Scheduling Simulator

## Group Members

* [Complete Name 1]
* [Complete Name 2]
* [Complete Name 3]

---

# Project Overview

This project implements a CPU Scheduling Simulator in C that models several classical operating system scheduling algorithms. The simulator executes workloads from input files, generates Gantt charts, computes scheduling metrics, and compares algorithm performance across different workload types.

The simulator supports standalone execution and is compatible with execution through `fork()` and `exec()`, simulating real operating-system process launching behavior.

---

# Implemented Algorithms

| Algorithm                                | Type           |
| ---------------------------------------- | -------------- |
| FCFS (First-Come, First-Served)          | Non-preemptive |
| SJF (Shortest Job First)                 | Non-preemptive |
| STCF (Shortest Time to Completion First) | Preemptive     |
| RR (Round Robin)                         | Preemptive     |
| MLFQ (Multi-Level Feedback Queue)        | Adaptive       |

---

# Implemented Features

* workload parsing from input files
* Gantt chart visualization
* turnaround/waiting/response time computation
* algorithm comparison mode
* workload benchmarking
* context-switch tracking
* edge-case testing
* modular scheduler architecture
* adaptive MLFQ scheduling
* priority boosting and starvation prevention

---

# MLFQ Configuration

| Queue | Policy      | Quantum          |
| ----- | ----------- | ---------------- |
| Q0    | Round Robin | 8                |
| Q1    | Round Robin | 24               |
| Q2    | Round Robin | 48               |
| Q3    | FCFS        | Until Completion |

Additional MLFQ features:

* dynamic priority demotion
* CPU allotment tracking
* periodic priority boosting
* starvation prevention

---

# Compilation Instructions

Compile the project using:

```bash
make
```

This generates the executable:

```bash
./schedsim
```

---

# Usage Instructions

## Run FCFS

```bash
./schedsim --algorithm FCFS --input test/quiz3.txt
```

---

## Run SJF

```bash
./schedsim --algorithm SJF --input test/quiz3.txt
```

---

## Run STCF

```bash
./schedsim --algorithm STCF --input test/quiz3.txt
```

---

## Run Round Robin

```bash
./schedsim --algorithm RR --quantum 30 --input test/quiz3.txt
```

---

## Run MLFQ

```bash
./schedsim --algorithm MLFQ --input test/quiz3.txt
```

---

# Comparison Mode

Compare all scheduling algorithms:

```bash
./schedsim --compare --input test/mixed.txt
```

Example output:

```text
=== Algorithm Comparison ===

Algorithm | Avg TT | Avg WT | Avg RT | Context Switches
----------|--------|--------|--------|------------------
FCFS      | 141.8  | 96.8   | 96.8   | 0
SJF       | 82.8   | 37.8   | 37.8   | 0
STCF      | 82.8   | 37.8   | 37.8   | 12
RR (q=30) | 128.0  | 83.0   | 33.5   | 28
MLFQ      | 119.0  | 74.0   | 11.5   | 15
```

---

# Demonstration Suite

Run the complete demonstration suite:

```bash
chmod +x test/test_suite.sh

cd test
./test_suite.sh
```

The test suite includes:

* algorithm verification
* interactive workloads
* CPU-bound workloads
* mixed workloads
* edge-case workloads
* workload comparison analysis

---

# Example Output

```text
=== Gantt Chart ===
[A------------][B---------][C-------]

Time: 0         240       420       570

=== Metrics ===

Process | AT  | BT  | FT  | TT  | WT  | RT
--------|-----|-----|-----|-----|-----|-----
A       |   0 | 240 | 240 | 240 |   0 |   0
B       |  10 | 180 | 420 | 410 | 230 | 230
C       |  20 | 150 | 570 | 550 | 400 | 400
```

---

# Metrics Computed

| Metric | Description     |
| ------ | --------------- |
| FT     | Finish Time     |
| TT     | Turnaround Time |
| WT     | Waiting Time    |
| RT     | Response Time   |

---

# Edge Cases Tested

The simulator was tested using:

* single-process workloads
* simultaneous arrivals
* identical burst times
* staircase arrivals
* zero-burst-time processes
* CPU-bound workloads
* interactive workloads
* mixed workloads
* large workloads with many processes

---

# Known Limitations

* Burst times are assumed to be known beforehand
* Context-switch cost is not explicitly simulated
* No I/O blocking simulation is implemented
* Time advances in discrete integer units
* Gantt chart visualization is simplified for readability
* MLFQ priorities are internal to scheduler logic only

---

# Design Assumptions

* Processes are CPU-bound unless otherwise specified
* Input workload files follow valid formatting
* Scheduling decisions occur at integer time boundaries
* Process arrival times are non-negative integers

---

# Technical Requirements Compliance

The simulator satisfies the required execution model:

* standalone executable operation
* compatibility with `fork()` and `exec()`
* command-line argument handling through `argv`
* standard I/O stream support
* modular source organization
* proper exit code behavior

