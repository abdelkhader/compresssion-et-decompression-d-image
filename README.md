# compresssion-et-decompression-d-image
Une image en 256 couleurs est codée par une matrice de pixels, chaque pixel prenant une valeur
entre 0 et 255. On veut représenter une telle image par un tableau de listes chaînées, la ième variable
du tableau représente la i+1ème ligne de l’image et contient un pointeur vers la liste des pixels de la
ligne.

Le stockage d’une image étant très onéreux en place mémoire, on voudrait compresser chaque ligne
de la manière suivante : remplacer toute suite de n pixels identiques (i.e., de même couleur, et donc
de même valeur v) par un couple (v, n).
Exemple : La ligne (5 5 5 5 5 5 5 5 5 2 2 2 2 2 2 2 2 2 2 2 2 2 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7)
sera remplacée par ((5, 9) (2, 13) (7, 17)).
