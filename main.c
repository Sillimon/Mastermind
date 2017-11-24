#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

//Structure du jeu MasterMind contenant
//  - La combinaison � deviner --> tableau de 4 entiers
//  - Le nombre d'essais restants au joueur pour deviner la combinaison --> int
//  - Le nombre de victoires du joueur --> int
//  - Le nombre de d�faites du joueur --> int
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

//Proc�dure g�n�rant une combinaison al�atoire � deviner
//Cette combinaison est stock�e dans les diff�rents index de partie.combinaison
//
//Param�tre : un pointeur de type struct joueur sur l'adresse de la structure partie
void genererCombinaison(struct jeu *partie)
{
    srand(time(NULL));
    int i;
    for(i = 0; i < 4; i++)
    {
        //G�n�re des chiffres de 0 � 9 et les stockent dans partie.combinaison[]
        partie->combinaison[i] = rand()%10;
    }
}

//Fonction qui compte le nombre de bon et de mauvais placements du joueur
//
//Param�tres : structure de type resultatTestCombinaison
//             un pointeur de type struct jeu sur l'adresse de partie
//             un pointeur de type int[] sur l'adresse du tableau de combinaisonJoueur
//
//Return : une structure de type resultatTestCombinaison
struct resultatTestCombinaison testerCombinaison(struct resultatTestCombinaison resultatTest, struct jeu *partie, int *combinaisonJoueur[])
{
    //D�finition/reset du nombre de bon et mauvais placements � 0
    resultatTest.nbrBonPlacement = 0;
    resultatTest.nbrMauvaisPlacement = 0;

    int i;
    for(i = 0; i < 4; i++)
    {
        //Incr�mentation du nombre de bon placements
        if(combinaisonJoueur[i] == partie->combinaison[i])
        {
            resultatTest.nbrBonPlacement++;
        }
        //Incr�mentation du nombre de mauvais placements
        //On v�rifie la combinaison du joueur � l'index i pour chaque index de partie.combinaison
        //le else if nous permet d'ignorer le cas o� combinaisonJoueur[i] == partie->combinaison[i]
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

    //D�claration des structures de type jeu et resultatTestCombinaison
    //puis d�finition du nombre de victoires et d�faites du joueur � 0
    struct jeu partie;
    struct resultatTestCombinaison resultatTest;
    partie.nbrVictoires = 0;
    partie.nbrDefaites = 0;

    //Enchaine les parties tant que le joueur choisi de rejouer
    //Joue au minimum une fois
    do
    {
        //Appel de la proc�dure g�n�rant une combinaison al�atoire � deviner
        genererCombinaison(&partie);

        //D�finition du nombre d'essais restants � 10
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

            //Stockage du choix dans les diff�rents index de combinaisonJoueur[]
            for(i = 0; i < 4; i++)
            {
                printf("\nChiffre %d : ", i+1);
                scanf("%d", &combinaisonJoueur[i]);
            }

            //Appel de la fonction comparant la combinaison du joueur
            //et celle g�n�r�e al�atoirement
            resultatTest = testerCombinaison(resultatTest, &partie, &combinaisonJoueur);

            printf("\n%d bon placements ET %d placements au mauvais endroit\n\n", resultatTest.nbrBonPlacement, resultatTest.nbrMauvaisPlacement);

            //D�cr�mentation du nombre d'essais du joueur
            partie.essaisRestant--;

            printf("Il vous reste %d essais !\n\n\n", partie.essaisRestant);
        }
        while(resultatTest.nbrBonPlacement != 4 && partie.essaisRestant > 0);

        //Incr�mentation du nombre de victoires ou de d�faites
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
