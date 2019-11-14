gcc -c -I$GRAPH init.c maitre_fenetres.c
ar rc outils_fenetre.a init.o maitre_fenetres.o
rm -f init.o maitre_fenetres.o
