#!/bin/bash
# run.sh
# Utilitário para automatizar a execução de testes
#
# Execute na forma "ferrametas/run.sh problemas/ecnu/2189"; isso irá compilar
# o executável ecnu/2189
#
# Definição do formato das entradas:
# Assumir-se-á que existe, em algum dos diretórios-pai, um arquivo chamado
# inputformat.sh. Para mais informações, veja problemas/inputformat.sh


# get_input_format( file_name, old_wd )
# Função que navegará até o diretório de file_name e procurará nos diretórios
# "ancestrais" por um arquivo chamado inputformat.sh, executando
# "source" neste arquivo. Após, retornamos para old_wd.
get_input_format() {
    cd $(dirname "$1")
    while true
    do
        if [ -e inputformat.sh ]
        then
            source inputformat.sh
            break
        fi
        cd ..
    done
    cd "$2"
}

# readflags()
# Função que criticará a entrada de dados e modificará as variáveis
# filename e CXX de acordo com sua semânticae
readflags() {
    if [ -z $1 ]
    then
        echo "Usage: $0 judge/file [compiler]"
        exit 1
    fi

    filename=$1

    CXX="g++ -std=c++11"
    if [ ! -z $2 ]
    then
        CXX=$2
    fi
}

# compile( filename )
# Função que compilará o prpgrama.
compile() {
    echo $CXX $filename
    $CXX $filename
}

# remove_extension( filename )
# Remove a extensão do nome do arquivo.
# Por conveniência, caso haja um caraactere alfabético precedido de um ponto
# antes do nome do arquivo, este é removido também.
# Por exemplo, abc.a.cpp vira abc
#              abc.4.cpp vira abc.4
#
# O valor de retorno é impresso em stdin.
remove_extension() {
    sed -e "s/\(\.[a-z]\)\?\.[a-z]*//" <<< "$1"
}


# main

set -e

readflags "$@"
compile "$filename"
get_input_format "$filename" "$(pwd)"
inputformat $filename

time_then=$(date +%s%N)

for file in $inputformat_files
do
    echo $file
    ./a.out < $file | diff - $($inputformat_sed <<< "$file")
done

time_now=$(date +%s%N)
milisseconds=$(dc -e "$time_now $time_then - 1000000 / n")
echo Tempo total: $milisseconds ms
