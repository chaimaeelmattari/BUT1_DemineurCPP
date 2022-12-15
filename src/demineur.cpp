/**
 * @file demineur.cpp
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
//#include "ConteneurTDE.h"
#include "probleme.h"
#include "grille.h"

using namespace std;

/**
 * @brief A partir d'une grille, produire un coup en fonction des cases  
 * libres, le type du coup M ou D est calculé eatoirement.
 * @see ConteneurTDE.cpp::detruire, pour sa désallocation en fin d'utilisation 
 */

void produire_coup(){
    
   int nb_li, nb_co;
   string ligne;
   cin >> nb_li >> nb_co;
   string type_coup="DMMD";

   ConteneurTDE cases_libre;
   initialiser(cases_libre,nb_li * nb_co,2);
   for(int i=0; i< nb_li  * nb_co; i++)
        ecrire(cases_libre,i,vide);
   for(int l=0;l<(nb_li-1) * 3 ;l++){
        getline(cin,ligne);
        if ( (l % 2) == 0 )
            for(int c=0;c<nb_co ;c++)
            if (ligne[c*4+2] == '.'){
                int position = (l/2 - 1) * nb_co + c; 
                ecrire(cases_libre,position,1);
            }
   }
    
    /* initialize random seed: */
     srand (time(NULL));
       
    int nbr_mine_generees=0;
    int rnd_pos;
    do{    
        rnd_pos = rand()%(nb_li * nb_co);
        if (lire(cases_libre,rnd_pos) == 1){
            break;
        }    
   } while(1);      // A améliorer 
    
    /* initialize random seed: pour ne pas generer les meêms valeurs */ 
     srand (time(NULL));
     cout << type_coup[rand()%(4)] << rnd_pos;
   detruire(cases_libre);
}

int main () {
    unsigned int code_operation;
    unsigned int nb_li, nb_co, nb_mines;

    cin >> code_operation;                                //Lecture de la commande      
	if (code_operation == 1) {            //
            cin >> nb_li >> nb_co >> nb_mines;
			produire_probleme(nb_li, nb_co, nb_mines);
        }
        if (code_operation == 2) {
            produire_grille(true);              
        }

        // 0 -> partie en cours, 1 -> partie perdue, 2 -> partie gangée 
        if (code_operation == 3){
           if(produire_grille(false) == gagne)
                   cout << "game won" << endl;
            else  
                  cout << "game not won" << endl;
        }

        if (code_operation == 4){
            if(produire_grille(false) == perdu)
                cout << "game lost" << endl;
            else  
                cout << "game not lost" << endl;
        }
        
        if (code_operation == 5) {
            string coup;
            int position=0;          
         produire_coup();
        }  
    return 0;    
}
   

