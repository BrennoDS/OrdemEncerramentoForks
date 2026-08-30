#!/bin/bash

TOTAL=150

echo "Iniciando $TOTAL experimentos(com sleep e tempo aleatorio, seed fixa)..."
echo

for i in $(seq 1 $TOTAL)
do
    echo "================================"
    echo "Experimento $i de $TOTAL"
    echo "================================"

    ./mainFixo "$i"

    echo
done

echo "================================"
echo "Todos os experimentos concluídos!"
echo "================================"