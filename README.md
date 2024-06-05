# CPPFight

## Description
Ce projet a pour but de valider nos compétences en C++ dans le cadre de notre formation en tant qu'ingénieurs du numérique à Télécom SudParis.  
Le jeu CPPFight vise à être rapide à produire tout en présentant une structure complexe et certaines contraintes permettant de monter en compétences efficacement.

## Type de jeu
Le jeu est un combat tour par tour 1 contre 1, où les deux parties ne peuvent agir que durant leur tour.  
Cependant, certains évènement *peuvent* faire en sorte que le joueur puisse avoir une influence pendant le tour de l'ordinateur.

## Synopsys du jeu
Dans ce jeu, inspiré de Pokémon et Undertale, vous devez vous **défendre**, vous-même et votre bébé, de monstres arrivant sur votre position.  
Pour se défaire des vilains monstres dépourvus d'âme et de clémence, vous devez vous amener à les mettre hors de nuire en leur infligeant des **dommages physiques**.  
Cependant, n'oubliez pas que votre enfant est juste à côté !! Il n'aime vraiment pas la violence et vous n'aimeriez sûrement pas qu'il termine avec une mauvaise éducation.  
Additionnellement, votre **mental** est lié à celui de votre bébé. S'il aperçoit *trop de violence*, il se sentira en danger, et vous serez probablement moins puissant à cause du stress qu'il vous provoquera.  
En revanche, certaines **actions** peuvent le rassurer, et en conséquence peuvent vous rendre plus fort.

# Pseudo GDD
## Histoire
Comme indiqué dans le synopsis, le joueur incarne une figure parentale devant protéger son bébé et elle-même.  
Les méchants monstres, qui sont en réalités des **C** et des **P**, ne savent qu'une chose : frapper pour devenir plus fort. Le joueur doit alors les empêcher de provoquer le mal et rendre inoffensif ces misérables créatures qui ne souhaitent que le chaos.  
Après avoir gagné de multiples batailles, le joueur tombe nez à nez avec le **boss des monstres** : le ***CPP++***.  
Celui ci est plus fort et demandra au joueur un "*common sens*" aguisé pour parvenir à vaincre ce monstre.

## Gameplay
Le jeu est gagné lorsque une suite d'un ou plusieurs combats ont été remportés par le joueur.

### Rencontre
Lors d'une **rencontre**, le joueur et le monstre opposant est engagé dans un combat tour par tour :
- La fuite n'est pas possible ;
- Le jeu se termine si les PV du joueur tombent à zéro ou en-dessous ;
- Le joueur remporte le combat et le jeu continue si les PV du monstres tombent à zéro ou en-dessous ;

### Attaque du joueur
Durant une rencontre, le joueur peut lorsque c'est son tour :
- Attaquer le monstre ;
- Effectuer une des actions possibles sur le monstre ;
- ***Se régénérer de la santé (PV)***

#### Attaquer le monstre
Le joueur se voit apparaître un mini-jeu de rythme (une barre traversant l'écran), qui lui permettra d'infliger des dégâts proportionnellement à sa performance.  
L'humeur du bébé est aussi pris en compte dans le calcul.

#### Effectuer une action
Plusieurs actions seront proposées au joueur. Certaines d'entre elles auront un impact positif sur l'humeur du bébé, tandis que d'autres auront, de manière surprenante, un impact négatif.

#### ***Se regénérer de la santé***
Le joueur pourrait avoir à sa disposition une certaine quantités d'items régénérants.  
Il en aurait en quantité limitée.


## Diagramme de classe
- [ ] Todo
