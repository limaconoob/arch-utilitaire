
gcc -c contenu.c dessin.c ecrire.c init_graph.c nettoyage.c
ar rc libgraphique.a contenu.o dessin.o ecrire.o init_graph.o nettoyage.o
rm -f contenu.o dessin.o ecrire.o init_graph.o nettoyage.o
