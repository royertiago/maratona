# inputformat.sh
# Configuração alternativa para o formato de entrada dos problemas
# da etapa regional da Maratona de programação 2014

inputformat() {
    local target=$(remove_extension "$1")
    inputformat_files=$target\_*.in
    inputformat_sed='sed s/\.in/\.sol/'
}
