
   # Travail pratique 3

   ## Description

   Le projet a été crée pour le cours *INF 3135 Hiver 2020* de l'*UQAM*.
   Le TP3 continue sur le sujet de la session  - le système MCAS de *Boeing*.

   ## Auteur

   Crée par IVAYLO IVANOV (IVAI08039506)

   ## Fonctionnement
  
  Ce projet lit une série d'instructions sous un format spécifique et génère
  des réponses dépendamment du type de l'instruction.
  
  Le TP3 modifie le TP2 en ajoutant des fonctionnalités avec différents paramètres d'entrée.
  Les arguments suivants sont gérés :
  >`-i`  information invalide : Affiche les transactions non reconnues 
  >`-d`  information détaillée : Affiche les informations pour chaque transaction
  >`-s`  information sommaire : Affiche le nombre total des transactions et erreurs
  >`-t`  information tranquille : Affiche seulement les informations `-i` `-d` ou `-t

Types de transactions d'entrée *STDIN* et format:
01: Changement d'état de l'appareil
>\<timestamp> \<01> \<etat>

02: Lecture d'un capteur d'angle d'incidence
>\<timestamp> \<02> \<sensor> \<valeur>

03: Lecture de longueur de l'ouverture d'un volet (gauche ou droite)
>\<timestamp> \<03> \<sensor> \<valeur>

04: Lecture d'un capteur de l'angle stabilisateur horizontal
>\<timestamp> \<04> \<sensor> \<valeur>

05: Erreur provenant d'un autre système
>\<timestamp> \<05> \<système> \<erreur>

Exemple de transactions du fichier 'text':
~~~bash
$cat text
100 02 A1 ERROR
101 02 A1 ERROR
102 02 A1 ERROR
104 05 11 08
105 05 11 12
109 05 11 55
120 02 A2 ERROR
125 02 A2 ERROR
129 02 A2 ERROR
130 05 11 0
~~~

Utiliser 'text' avec tp3:
~~~bash
cat text | ./tp3 -d -i -s> output 
~~~
Résultat
~~~bash
$ cat output 
Version #: ..1000906 13 100 A1
06 13 100 A1
06 13 101 A1
06 13 102 A1
06 13 120 A2
06 13 125 A2
06 13 129 A2
MCAS IS OFF
07 11 130
MCAS IS ON
-----------------
Transactions non renonnues
Transactions non valides: 0
Timestamp non valide: 0
-----------------
Information detaillee
Transaction no. 1 : 0
Transaction no. 2 : 6
Transaction no. 3 : 0
Transaction no. 4 : 0
Transaction no. 5 : 4
-----------------
Information sommaire
Transactions valides: 10
Transactions recues: 10
-----------------
~~~

   
   ## Contenu du projet

   #### Makefile : Contient des commandes pour gérer les dépendances:
   
   `make tp3` Crée l'exécutable *tp3*
   `make lib` Télécharge les fichiers *flop.h* et *flop.o*
   `make` Pour starter l'exécutable tp3 en mode interactif `./tp3`
    `make clean` Pour effacer les fichiers `*.o` et `flop.h`  
	    
#### malib.h : Contient les prototypes de `malib.c`
#### malib.c : Contient les fonctions créés par moi pour ce TP
#### flop.h et flop.c : Contient les fonctions fournies par le professeur
#### tp3.c : Contient le programme principal et la fonction `main`
#### 'text' est un fichiers text pour passer des test et les écrire dans 'output'
#### Reflection est un fichier qui décris mon cheminement du cours INF3135

   ## Processus de réflexion et démarche 
   ##### Décris en détail dans le fichier 'Reflection'.
 Ma démarche pour le TP3 était de commencer par refaire le TP2 au complet et m'assurer que
 le programme est fonctionnel et conforme aux exigences. J'ai refait mon `Makefile` et j'ai
 déplace mes fonctions dans `malib.c` et `malib.h`.
 
 Une fois que le projet fonctionnait selon le TP2, j'ai modifie `tp3.c`, `malib.c`, et `malib.h`pour les nouvelles exigences du TP3.

Le plus gros défi était de transiger du mode TP2 au mode TP3 et surtout avec l'argument 
`-t mode tranquille`, car avant de débuter le TP3, j'avais mis mes `printf()` pour les messages d'erreur dans les foncions ex. `log_erreur()`, `log_err_valeur()`

J'avais soit l'option de passer un paramètre `bool` pour valider si la fonction va imprimer le message ou non, ou de faire sortir tous les `printf()` en dehors de mes fonctions.
J'ai décide de sortir mes `printf()` de `malib.c` et faire un seul `printf()` à la fin de la fonction `main()` dans `tp3.3`

J'ai choisi cette option, car j'aurai moins de chances de me tromper et oublier de passer un paramètre `bool` ou de gérer la condition du `bool` que de faire sortir mes `printf()` en changeant les  `void log_erreur()`, `void log_err_valeur()` à `int log_erreur()`et 
`int log_err_valeur()` et changer les `printf()`avec `sprintf()`

   ## Références

[Github inf315](https://github.com/guyfrancoeur/INF3135_H2020)
[Cplusplus](http://www.cplusplus.com/)
[OnlineGDB](https://www.onlinegdb.com/online_c_compiler)
[GeeksForGeeks](https://www.geeksforgeeks.org/)
<sub><sup>[StackOverflow](https://github.com/guyfrancoeur/INF3135_H2020) </sup></sub>
</Jaifaitmespushups>



   ## Statut et auto-évaluation

   Le projet est complété, mais j'aurais aimé améliorer mon code, car il y a de la répétition du code.
