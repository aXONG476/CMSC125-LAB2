#!/bin/bash

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
echo "- adaptive scheduling"
echo ""

#
# Interactive workload
#
echo "====================================="
echo " MLFQ INTERACTIVE WORKLOAD"
echo "====================================="

../schedsim \
--algorithm MLFQ \
--input interactive.txt

echo ""
echo "Expected behavior:"
echo "- short jobs remain high priority"
echo "- fast response times"
echo ""

#
# INTERACTIVE WORKLOAD COMPARISON
#
echo "====================================="
echo " INTERACTIVE WORKLOAD COMPARISON"
echo "====================================="

../schedsim \
--compare \
--input interactive.txt

echo ""
echo "Expected observations:"
echo "- STCF and MLFQ achieve best response times"
echo "- FCFS may suffer convoy effects"
echo "- RR improves responsiveness"
echo ""

#
# CPU-heavy workload
#
echo "====================================="
echo " MLFQ CPU-BOUND WORKLOAD"
echo "====================================="

../schedsim \
--algorithm MLFQ \
--input cpu_bound.txt

echo ""
echo "Expected behavior:"
echo "- long jobs gradually demoted"
echo "- lower queues reduce context switching"
echo ""

#
# CPU-BOUND WORKLOAD COMPARISON
#
echo "====================================="
echo " CPU-BOUND WORKLOAD COMPARISON"
echo "====================================="

../schedsim \
--compare \
--input cpu_bound.txt

echo ""
echo "Expected observations:"
echo "- FCFS and larger-quantum MLFQ reduce overhead"
echo "- RR causes more context switches"
echo "- throughput becomes more important"
echo ""

#
# Mixed workload
#
echo "====================================="
echo " MLFQ MIXED WORKLOAD"
echo "====================================="

../schedsim \
--algorithm MLFQ \
--input mixed.txt

echo ""
echo "Expected behavior:"
echo "- interactive jobs finish quickly"
echo "- CPU-heavy jobs migrate downward"
echo ""

#
# MIXED WORKLOAD COMPARISON
#
echo "====================================="
echo " MIXED WORKLOAD COMPARISON"
echo "====================================="

../schedsim \
--compare \
--input mixed.txt

echo ""
echo "Expected observations:"
echo "- MLFQ adapts best to mixed workloads"
echo "- STCF improves short-job responsiveness"
echo "- FCFS may delay short interactive tasks"
echo ""

#
# Edge case
#
echo "====================================="
echo " EDGE CASE TEST"
echo "====================================="

../schedsim \
--algorithm FCFS \
--input zero.txt

echo ""
echo "Edge case completed successfully"
echo ""

echo "====================================="
echo " ALL TESTS COMPLETE"
echo "====================================="