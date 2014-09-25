#!/bin/bash
# run.sh
# Utilitário para automatizar a execução de testes
#
# Execute na forma "ferrametas/run.sh problemas/ecnu/2189"; isso irá compilar
# o executável ecnu/2189

if [ -z $1 ]
then
    echo "Usage: $0 judge/file"
    exit 1
fi

TARGET=$1
CXX=g++
if [ ! -z $2 ]
then
    CXX=$2
fi

# Para que possamos lidar com targets da forma spoj-br/express11.a,
# precisamos remover aquele ".a" do final.
STARGET=`sed -e "s/\.[a-z]//" <<< $TARGET` # "stripped target"

INPUT=$STARGET.in*
OUTPUT=(`sed "s/\.in/\.out/" <<< "$INPUT"`)
INPUT=($INPUT)
# Agora, INPUT e OUTPUT são arrays "pareados".

set -e # Primeiro comando com status não-zero encerra execução

echo $CXX -std=c++11 $TARGET.cpp
$CXX -std=c++11 $TARGET.cpp

THEN=`date +%s%N`

for((i=0;i<${#INPUT[@]};++i)); do
    echo ${INPUT[i]}
    ./a.out < ${INPUT[i]} | diff - ${OUTPUT[i]}
done

NOW=`date +%s%N`
MS=`dc -e "$NOW $THEN - 1000000 / n"`
echo Tempo total: $MS ms
