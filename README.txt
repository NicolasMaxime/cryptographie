Le programme est proposé par :
Ipseiz Angela, 
Li-Cho Dylan, 
Nicolas Maxime

Pour compiler les sources, se mettre dans le répertoire racine et faire 
$> make

Pour nettoyer le dossier : 
$> make fclean

Pour executer le programme, après avoir compiler faire : 

$> ./crypto



Dans un premier temps apparaissent 10 tests pour comparer les résultats entre ExpMod fait par notre groupe, et mpz_powm de la lib gmp.
Dans un second temps un test de la signature de shnorr avec un message valide, puis ensuite un message erroné. 
Enfin, 100 tests sur des message généré aléatoirement à l’aide de la fonction random.

Nous avons eu un probleme sur le keygen pour trouver le g (le temps d’attente était très long)
Ainsi, pour ne pas être bloqué, nous avons choisit les valeurs arbitraires de 
q = 7919, k = 8
p = 63353
g = 1241

