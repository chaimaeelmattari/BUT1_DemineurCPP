/**
 * @file probleme.cpp
 * Projet création du démineur
 * @authors Chaimae EL MATTARI, Cedric TANGHE 
 * @version 1.0 - 09/01/2022
 * @brief 
 * 
 */
#include<iostream>
#include<cstdlib>
#include <random>
#include <ctime>
#include <cassert>
#include <string>
#include "ConteneurTDE.h"

using namespace std;

/**
 * @brief Initialise un conteneur d'items
 * Allocation en mémoire dynamique du conteneur d'items
 * de capacité (capa) extensible par pas d'extension (p)
 * @see detruire, pour sa désallocation en fin d'utilisation 
 * @param[out] c : le conteneur d'items
 * @param [in] capa : capacité du conteneur
 * @param [in] p : pas d'extension de capacité
 * @pre capa>0 et p>0
 */
void produire_probleme (unsigned int nb_li, unsigned int nb_col, unsigned int nb_mines){
    ConteneurTDE list_mines;
    initialiser(list_mines,nb_mines,2);

    /* initialize random seed: */
     srand (time(NULL));
       
    int nbr_mine_generees=0;

    cout << nb_li << " " << nb_col << " " << nb_mines ;
    do{    
        //int randNum = rand()%(max-min + 1) + min;
        int rnd_mine = rand()%(nb_li * nb_col);
        if ( ! contenir(list_mines,rnd_mine)){
            ecrire(list_mines,nbr_mine_generees,rnd_mine);
            nbr_mine_generees++;
            cout << " " << rnd_mine;
        }

    }while ( nbr_mine_generees < nb_mines);
    cout << endl;
    /* Désallouer le conteneur de list_mines */
	detruire(list_mines);
}