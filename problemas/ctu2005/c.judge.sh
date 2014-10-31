# c.judge.sh
# Juíz especial para ponto flutuante.

# Reformata a entrada para trocar todas os números por X, e os -0.0000 por X.XXXX.
# O objetivo é preparar a entrada para rodar um diff contra apenas a "aparência"
# do arquivo de entrada, e deixar as diferenças de ponto flutuante para fpdiff.
judge_reformat() {
    sed -e 's/-\(0*.0\+\|0\+.0*\)/\1/g' $1 | sed -e 'y/0123456789/XXXXXXXXXX/'
    # Embora essa reformatação esteja sujeita a -0.005 (pois o 5 não faz parte
    # da expressão regular), não há problema pois ferramentas/fpdiff 
    # dá conta do resto.
}

judge_function() {
    ferramentas/fpdiff $2 $3 0.01 && default_judge $1 <(judge_reformat $2) <(judge_reformat $3)
}
