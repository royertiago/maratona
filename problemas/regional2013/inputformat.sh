# inputformat.sh
# Configuração alternativa para o formato de entrada dos problemas
# da etapa regional da Maratona de programação 2014

inputformat() {
    local target=$(dirname "$1")
    inputformat_files=$target/input/*
    inputformat_sed='sed s/\input/\output/'
}
