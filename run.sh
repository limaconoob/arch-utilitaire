export GRAPH=/tmp/arch-utilitaire/libgraphique/bibliotheque/
export DAEMON=/tmp/arch-utilitaire/gestionnaire_de_fenetres/daemon/
export LILITHIA=/tmp/lilithia
cd $GRAPH
sh run.sh
cd $DAEMON
sh bib.sh
sh run.sh
cd $LILITHIA
sh run.sh
./JEU

