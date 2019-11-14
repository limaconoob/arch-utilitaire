
gcc -c dessin.c ecrire.c init.c nettoyage.c protocole_entrees.c
ar rc libgraphique.a dessin.o ecrire.o init.o nettoyage.o protocole_entrees.o
rm -f dessin.o ecrire.o init.o nettoyage.o protocole_entrees.o
##gcc -lm -lpthread libgraphique.a -o entrees
