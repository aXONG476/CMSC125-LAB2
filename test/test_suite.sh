#!/bin/bash

LOG_FILE="output.log"

exec > "$LOG_FILE" 2>&1

echo "====================================="
echo " CMSC 125 Lab 2 Demonstration Suite"
echo "====================================="

echo ""

#
# FCFS
#
echo "====================================="
echo " FCFS TEST"
echo "====================================="

../schedsim \
--algorithm FCFS \
--input quiz3.txt

echo ""
echo "Expected Average TT: 515"
echo ""

#
# SJF
#
echo "====================================="
echo " SJF TEST"
echo "====================================="

../schedsim \
--algorithm SJF \
--input quiz3.txt

echo ""
echo "Expected Average TT: 461"
echo ""

#
# STCF
#
echo "====================================="
echo " STCF TEST"
echo "====================================="

../schedsim \
--algorithm STCF \
--input quiz3.txt

echo ""
echo "Expected Average TT: 393"
echo ""

#
# RR
#
echo "====================================="
echo " RR TEST (Quantum = 30)"
echo "====================================="

../schedsim \
--algorithm RR \
--quantum 30 \
--input quiz3.txt

echo ""
echo "Expected Average TT: 627"
echo ""

#
# MLFQ
#
echo "====================================="
echo " MLFQ TEST"
echo "====================================="

../schedsim \
--algorithm MLFQ \
--input quiz3.txt

echo ""
echo "MLFQ demonstrates:"
echo "- multiple priority queues"
echo "- dynamic demotion"
echo "- allotment tracking"
echo "- priority boosting"
echo "- adaptive scheduling"
echo ""

#
# INTERACTIVE WORKLOAD
#
echo "====================================="
echo " INTERACTIVE WORKLOAD"
echo "====================================="

../schedsim \
--algorithm MLFQ \
--input interactive.txt

echo ""

#
# INTERACTIVE COMPARISON
#
echo "====================================="
echo " INTERACTIVE WORKLOAD COMPARISON"
echo "====================================="

../schedsim \
--compare \
--input interactive.txt

echo ""

#
# CPU-BOUND WORKLOAD
#
echo "====================================="
echo " CPU-BOUND WORKLOAD"
echo "====================================="

../schedsim \
--algorithm MLFQ \
--input cpu_bound.txt

echo ""

#
# CPU-BOUND COMPARISON
#
echo "====================================="
echo " CPU-BOUND WORKLOAD COMPARISON"
echo "====================================="

../schedsim \
--compare \
--input cpu_bound.txt

echo ""

#
# MIXED WORKLOAD
#
echo "====================================="
echo " MIXED WORKLOAD"
echo "====================================="

../schedsim \
--algorithm MLFQ \
--input mixed.txt

echo ""

#
# MIXED COMPARISON
#
echo "====================================="
echo " MIXED WORKLOAD COMPARISON"
echo "====================================="

../schedsim \
--compare \
--input mixed.txt

echo ""

#
# SINGLE PROCESS EDGE CASE
#
echo "====================================="
echo " SINGLE PROCESS TEST"
echo "====================================="

../schedsim \
--algorithm FCFS \
--input zero.txt

echo ""

#
# SIMULTANEOUS ARRIVAL TEST
#
echo "====================================="
echo " SIMULTANEOUS ARRIVAL TEST"
echo "====================================="

../schedsim \
--algorithm SJF \
--input simultaneous.txt

echo ""

#
# IDENTICAL BURST TEST
#
echo "====================================="
echo " IDENTICAL BURST TEST"
echo "====================================="

../schedsim \
--algorithm SJF \
--input identical.txt

echo ""

#
# STAIRCASE ARRIVAL TEST
#
echo "====================================="
echo " STAIRCASE ARRIVAL TEST"
echo "====================================="

../schedsim \
--algorithm STCF \
--input staircase.txt

echo ""

echo "====================================="
echo " ALL TESTS COMPLETE"
echo "====================================="

echo ""
echo "Output saved to: $LOG_FILE"