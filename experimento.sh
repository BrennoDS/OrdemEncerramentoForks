#!/bin/bash

TOTAL=150

echo "Iniciando $TOTAL experimentos(com sleep e tempo aleatorio, seed aleatoria)..."
echo

for i in $(seq 1 $TOTAL)
do
    echo "================================"
    echo "Experimento $i de $TOTAL"
    echo "================================"

    ./main "$i"

    echo
done

echo "================================"
echo "Todos os experimentos concluídos!"
echo "================================"