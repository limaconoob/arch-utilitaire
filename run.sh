
## Cette commande met l'utilisateur courant dans le groupe pour lire les entrées
## Il faut redémarrer l'OS (au moins la session) pour que la modification ait effet
# sudo usermod -a -G `stat -c '%G' /dev/input/mice` `whoami`

export GRAPH=$HOME/arch-utilitaire/libgraphique/bibliotheque/
# export DAEMON=$HOME/arch-utilitaire/gestionnaire_de_fenetres/daemon/
export DAEMON=$HOME/debug-arch/gestionnaire_de_fenetres/daemon/
export LILITHIA=$HOME/lilithia

# rm -f $DAEMON/.sock/*
killall DAEMON_INPUT

cd $GRAPH
sh run.sh
cd $DAEMON
sh bib.sh
sh run.sh
cd $LILITHIA
sh run.sh
./JEU

