#inputformat.sh
# Arquivo de configuração padrão do formato de entrada.
#
# Como os formatos de entrada para os problemas variam de acordo
# com a competição (e, possivelmente, o ano), não é possível/elegante
# utilizar um formato unificado para todos os problemas.
# Este arquivo resolve o problema de forma parcial.
#
# Cada código fonte deve estar localizado num diretório que possui,
# em algum dos diretórios "ancestrais" (diretório pai, ou pai do pai...),
# um arquivo chamado inputfomat.sh. Neste arquivo, deve existir
# a definição de uma função "inputformat", que receberá como parâmetro
# o nome do arquivo a ser compilado (o nome completo do código fonte)
# e deve escrever, nas variáveis globais inputformat_files e 
# inputformat_sed, como segue:
#
#   inputformat_files: a lista de arquivos de entrada
#   inputformat_sed: script sed (ou algum outro script) que transforma um nome
#                    de arquivo de entrada num arquivo de saída.
#
# Outras variáveis globais e funções podem ser definidas, desde que prefixadas
# com "inputformat_".
# Na existência de múltiplos inputformat.sh, o escolhido é o mais aninhado.
#
# Este arquivo contém as transformações usadas para contemplar o formato
# de de entrada descrito no arquivo problemas/README.md.

inputformat() {
    local target=$(remove_extension "$1")
    inputformat_files=$target.in*
    inputformat_sed='sed s/\.in/\.out/'
}
