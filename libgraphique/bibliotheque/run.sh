
gcc -c dessin.c ecrire.c init.c nettoyage.c
ar rc libgraphique.a dessin.o ecrire.o init.o nettoyage.o
rm -f dessin.o ecrire.o init.o nettoyage.o
gcc protocole_entrees.c -lm libgraphique.a -o souris
