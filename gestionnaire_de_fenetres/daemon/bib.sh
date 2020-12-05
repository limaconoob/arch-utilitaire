gcc -c attache_entrees.c lit_entrees.c -I$GRAPH
ar rc libdaemon.a attache_entrees.o lit_entrees.o
rm -f attache_entrees.o lit_entrees.o
