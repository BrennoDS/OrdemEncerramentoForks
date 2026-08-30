#!/bin/bash

TOTAL=150

echo "Iniciando $TOTAL experimentos(sem sleep)..."
echo

for i in $(seq 1 $TOTAL)
do
    echo "================================"
    echo "Experimento $i de $TOTAL"
    echo "================================"

    ./mainNoSleep "$i"

    echo
done

echo "================================"
echo "Todos os experimentos concluídos!"
echo "================================"