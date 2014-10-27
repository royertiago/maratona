# makefile
# Constrói a única ferramenta usada por run.sh: fpdiff
ferramentas/fpdiff: ferramentas/fpdiff.c
	gcc ferramentas/fpdiff.c -o ferramentas/fpdiff -O2
