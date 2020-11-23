gcc -c attache_input.c -I$GRAPH
ar rc libdaemon.a attache_input.o
rm -f attache_input.o
