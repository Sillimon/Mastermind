#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

//Structure du jeu MasterMind contenant
//  - La combinaison à deviner --> tableau de 4 entiers
//  - Le nombre d'essais restants au joueur pour deviner la combinaison --> int
//  - Le nombre de victoires du joueur --> int
//  - Le nombre de défaites du joueur --> int
struct jeu
{
    int combinaison[4];
    int essaisRestant;
    int nbrVictoires;
    int nbrDefaites;
};

//Structure contenant
//  - Le nombre de bon placements dans la combinaison du joueur --> int
//  - Le nombre de placements au mauvais endroit dans la combinaison du joueur--> int
struct resultatTestCombinaison
{
    int nbrBonPlacement;
    int nbrMauvaisPlacement;
};

//Procédure générant une combinaison aléatoire à deviner
//Cette combinaison est stockée dans les différents index de partie.combinaison
//
//Paramètre : un pointeur de type struct joueur sur l'adresse de la structure partie
void genererCombinaison(struct jeu *partie)
{
    srand(time(NULL));
    int i;
    for(i = 0; i < 4; i++)
    {
        //Génère des chiffres de 0 à 9 et les stockent dans partie.combinaison[]
        partie->combinaison[i] = rand()%10;
    }
}

//Fonction qui compte le nombre de bon et de mauvais placements du joueur
//
//Paramètres : structure de type resultatTestCombinaison
//             un pointeur de type struct jeu sur l'adresse de partie
//             un pointeur de type int[] sur l'adresse du tableau de combinaisonJoueur
//
//Return : une structure de type resultatTestCombinaison
struct resultatTestCombinaison testerCombinaison(struct resultatTestCombinaison resultatTest, struct jeu *partie, int *combinaisonJoueur[])
{
    //Définition/reset du nombre de bon et mauvais placements à 0
    resultatTest.nbrBonPlacement = 0;
    resultatTest.nbrMauvaisPlacement = 0;

    int i;
    for(i = 0; i < 4; i++)
    {
        //Incrémentation du nombre de bon placements
        if(combinaisonJoueur[i] == partie->combinaison[i])
        {
            resultatTest.nbrBonPlacement++;
        }
        //Incrémentation du nombre de mauvais placements
        //On vérifie la combinaison du joueur à l'index i pour chaque index de partie.combinaison
        //le else if nous permet d'ignorer le cas où combinaisonJoueur[i] == partie->combinaison[i]
        else if(combinaisonJoueur[i] == partie->combinaison[0]
                || combinaisonJoueur[i] == partie->combinaison[1]
                || combinaisonJoueur[i] == partie->combinaison[2]
                || combinaisonJoueur[i] == partie->combinaison[3])
        {
            resultatTest.nbrMauvaisPlacement++;
        }
    }

    return resultatTest;
}



int main()
{
    srand(time(NULL));

    int i;
    int rejouer = 1;

    //Déclaration des structures de type jeu et resultatTestCombinaison
    //puis définition du nombre de victoires et défaites du joueur à 0
    struct jeu partie;
    struct resultatTestCombinaison resultatTest;
    partie.nbrVictoires = 0;
    partie.nbrDefaites = 0;

    //Enchaine les parties tant que le joueur choisi de rejouer
    //Joue au minimum une fois
    do
    {
        //Appel de la procédure générant une combinaison aléatoire à deviner
        genererCombinaison(&partie);

        //Définition du nombre d'essais restants à 10
        partie.essaisRestant = 10;


        //Demander au joueur de choisir une combinaison
        //Stcokage dans un tableau d'entiers de taille 4
        int combinaisonJoueur[4];

        //Jouer tant que le joueur n'a pas la bonne combinaison et qu'il a des essais
        //Joue au minimum une fois
        do
        {
            //Le joueur propose une combinaison
            printf("\n\nDevinez la combinaison :");

            //Stockage du choix dans les différents index de combinaisonJoueur[]
            for(i = 0; i < 4; i++)
            {
                printf("\nChiffre %d : ", i+1);
                scanf("%d", &combinaisonJoueur[i]);
            }

            //Appel de la fonction comparant la combinaison du joueur
            //et celle générée aléatoirement
            resultatTest = testerCombinaison(resultatTest, &partie, &combinaisonJoueur);

            printf("\n%d bon placements ET %d placements au mauvais endroit\n\n", resultatTest.nbrBonPlacement, resultatTest.nbrMauvaisPlacement);

            //Décrémentation du nombre d'essais du joueur
            partie.essaisRestant--;

            printf("Il vous reste %d essais !\n\n\n", partie.essaisRestant);
        }
        while(resultatTest.nbrBonPlacement != 4 && partie.essaisRestant > 0);

        //Incrémentation du nombre de victoires ou de défaites
        if(resultatTest.nbrBonPlacement == 4)
        {
            partie.nbrVictoires++;
        }
        else if(partie.essaisRestant <= 0)
        {
            partie.nbrDefaites++;
        }

        system("pause");
        system("cls");


        //Annonce du score total
        printf("Score total : \nNombre de victoires : %d \nNombre de defaites : %d\n\n", partie.nbrVictoires, partie.nbrDefaites);

        //Demande au joueur si il souhaite rejouer
        do
        {
            printf("Souhaitez-vous rejouer ? [1]Oui  [0]Non\n\n");
            scanf("%d", &rejouer);
        }
        while(rejouer != 0 && rejouer != 1);
    }
    while(rejouer == 1);

    return 0;
}
