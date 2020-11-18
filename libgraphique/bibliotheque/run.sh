
gcc -c contenu.c dessin.c ecrire.c init_graph.c nettoyage.c protocole_entrees.c
ar rc libgraphique.a contenu.o dessin.o ecrire.o init_graph.o nettoyage.o protocole_entrees.o
rm -f contenu.o dessin.o ecrire.o init_graph.o nettoyage.o protocole_entrees.o
##gcc -lm -lpthread libgraphique.a -o entrees
