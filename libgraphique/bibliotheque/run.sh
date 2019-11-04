
gcc -c clear.c dessin.c ecrire.c init.c
ar rc libgraphique.a clear.o dessin.o ecrire.o init.o
rm -f clear.o dessin.o ecrire.o init.o
