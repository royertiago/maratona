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
#
# Opcionalmente, um arquivo .judge.sh, com mesmo nome do arquivo de entrada,
# pode ser fornecido para executar o julgamento; este arquivo deve definir
# uma função judge_function, que será executada com três parâmetros:
#  <arquivo de entrada> <arquivo de saída> <saída do programa>
# O arquivo de saída será obtido a partir do inputformat_sed.
# A função deve retornar um valor numérico igual a zero para indicar aceitação
# da entrada, ou diferente de zero para indicar rejeição.
# Outras variáveis globais e funções podem ser definidas, desde que prefixadas
# com "judge_".


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
# Função que criticará a entrada de dados e modificará filename de acordo.
readflags() {
    if [ -z $1 ]
    then
        echo "Usage: $0 judge/file"
        exit 1
    fi

    filename=$1
}

# compile( filename )
# Função que compilará o prpgrama.
# A função altera a variável global CXX para corresponder ao comando de
# compilação executado.
compile() {
    CXX="g++ -std=c++11 -O2 -w $filename"
    $CXX
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


# Funções que contam o tempo.
# As variáveis globais clock_counted e clock_tmp são usadas
# para manter o estado do relógio.

# clock_reset()
# Reinicia a contagem do tempo.
clock_reset() {
    clock_counted=0
}

# clock_start
# Inicia a contagem do tempo.
clock_start() {
    clock_tmp=$(date +%s%N)
}

# clock_stop
# Para a contagem do tempo
clock_stop() {
    local tmp=$(date +%s%N)
    clock_counted=$((tmp - clock_tmp + clock_counted))
}

# clock_ms()
# Escreve na tela a quantidade de milissegundos medidos pelo relógio.
clock_ms() {
    echo $((clock_counted / 1000000))
}

# judge_default (ignored) correct_solution program_output
# Julgamento padrão: executa diff da entrada.
default_judge() {
    diff $3 $2 > /dev/null
}

# main

readflags "$@"
compile
if [ $? -ne 0 ]
then
    echo $CXX
    echo "CE - Compilation Error"
    exit 1
fi
get_input_format "$filename" "$(pwd)"
inputformat $filename

optional_judge_file=$(remove_extension $filename).judge.sh

if [ -f $optional_judge_file ]
then
    source $optional_judge_file
    judge=judge_function
else
    judge=default_judge
fi

clock_reset

for file in $inputformat_files
do
    tempfile=$(mktemp XXXXX_program_output)
    clock_start

    # Isso redireciona erros de execução para /dev/null.
    { ./a.out < $file > $tempfile; } >& /dev/null

    if [ $? -ne 0 ]
    then
        echo "RE - Runtime Error"
        rm $tempfile
        exit 1
    fi
    clock_stop
    $judge $file $($inputformat_sed <<< "$file") $tempfile
    if [ $? -ne 0 ]
    then
        echo "WA - Wrong Answer"
        rm $tempfile
        exit 1
    fi
    rm $tempfile
done

echo AC - Accepted - Total runtime: $(clock_ms) ms
