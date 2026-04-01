#!/bin/bash
# Script para comprobar posibles fugas de memoria en el programa
# Uso: ./memcheck.sh [-t] (flag -t para evaluar sobre los tests)
# Hay que tener instalado valgrind para ejecutar este script

if [ $# -eq 0 ]; then
    make
    valgrind --leak-check=full ./main
elif [ "$1" = "-t" ]; then
    make test
    valgrind --leak-check=full ./test
else
    echo "Usage: $0 [-t]"
fi