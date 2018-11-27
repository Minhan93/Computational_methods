#!/bin/bash
for dim in 60 90 200; do
    for which in 0 1 2 3 4 5 ; do
        for dense in 0.1  0.2 0.3; do
            echo $dim $which $dense
            ./matmult $dim $which $dense
        done
    done
done
