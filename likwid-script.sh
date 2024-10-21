#!/bin/bash

TEMP_OUTPUT=$(mktemp)

likwid-perfctr -C 0 -g FLOPS_DP -m ./inversa > "$TEMP_OUTPUT"

cat "$TEMP_OUTPUT" | awk '/\/begin-output/,/\/end-output/' | sed '/\/begin-output/d' | sed '/\/end-output/d' 
echo
cat "$TEMP_OUTPUT" | grep -E "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE|DP MFLOP/s" | grep -v "AVX"

rm "$TEMP_OUTPUT"

