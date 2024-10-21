#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Uso: $0 <caminho_do_programa_inversa>"
    exit 1
fi

INVERSE_PROGRAM=$1

TEMP_OUTPUT=$(mktemp)

$INVERSE_PROGRAM > "$TEMP_OUTPUT"

cat "$TEMP_OUTPUT"

# Usa o LIKWID para medir as operações aritméticas de ponto flutuante com o grupo FLOPS_DP
# e filtra para exibir apenas os contadores desejados
likwid-perfctr -C 0 -g FLOPS_DP -m $INVERSE_PROGRAM | grep -E "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE|DP \[MFLOP/s\]"

rm "$TEMP_OUTPUT"

