#/bin/bash
# comp.sh
# Script que redireciona os parâmetros de entrada para o gcc,
# ativando vários warnings.

g++ -Wall -Wextra -Wpedantic -Wunused -Wfloat-equal -Wlogical-op \
    -Wconversion -Wuseless-cast -Wtype-limits -Wchar-subscripts \
    -Wunreachable-code -Wshadow -Wwrite-strings -Wformat=2 \
    "$@"