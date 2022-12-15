
/**
 * @file grille.cpp
 * Projet création du démineur
 * @authors Chaimae EL MATTARI, Cedric TANGHE 
 * @version 1.0 - 09/01/2022
 * @brief contient touts les fonctions necessaires pour la gestion 
 * de la grille  
 * 
 */

#include<iostream>
#include<cstdlib>
#include <random>
#include <ctime>
#include <cassert>
#include <string>
#include "ConteneurTDE.h"
#include "grille.h"

using namespace std;

bool jouer_coup(grille& g, string coup);
void afficher_grille (const grille& g);

/**
 * @brief Initialise la grille
 * la structure grille contient deux tabaleau (dynamiques)
 * Le premier enrigistre les valaeur des cases: 
 *  - voir enum contenu_case { mine=-1, vide}
 * Le deuxieme tableau enrgistre l'etat des cases
 *  - voir enum contenu_case { mine=-1, vide}
 * @see ConteneurTDE
 * @param[in,out] g : la grille à initialiser
 */
void intialiser_grille(grille& g){
    initialiser(g.donnee_cases,g.lignes * g.colonnes,2);
    initialiser(g.etat_cases,g.lignes * g.colonnes,2);

    for(int i=0;i<g.lignes * g.colonnes;i++){
        // toutes las ceses sont  vide =0
        ecrire(g.donnee_cases,i,vide);
        // pour signifier que toutes les cases sont masquées
        ecrire(g.etat_cases,i,masque);

    }
}

/**
 * @brief Ajouter une mine à la grille en mettant à jour 
 *        les tableaux donnee_cases et etat_cases
 * @param[in,out] g : grille 
 * @param [in] idx_mine : position de la mine dans les tableaux
 *                        dynamiques donnee_cases et donnee_cases   
 */
void ajouter_mine(grille& g, int idx_mine){
    // calcul des ligne et colonne en fonction de la position idx_mine
    // corespondance entre tableau 2 dimension avec tableau double dimensions
    int li   = idx_mine / g.colonnes;
    int co = idx_mine % g.colonnes;
    ecrire(g.donnee_cases,idx_mine,mine);
        
    // On traite les cases adjacentes à la mine
    // li - 1, co -1     
    if (( li -1 > -1 ) && ( co -1 > -1) && (lire(g.donnee_cases,(li - 1) * g.colonnes + (co - 1)) != mine)) 
        ecrire(g.donnee_cases,(li - 1) * g.colonnes + (co - 1),lire(g.donnee_cases,(li - 1) * g.colonnes + (co - 1)) +1);
                       
    // li - 1, même co que la mine 
    if ( ( li -1 > -1 ) && (lire(g.donnee_cases,(li - 1) * g.colonnes + co) != mine)) 
        ecrire(g.donnee_cases,(li - 1) * g.colonnes + co,lire(g.donnee_cases,(li - 1) * g.colonnes + co) +1);
                    
    // li - 1 co +1 
    if (( li -1 > -1 ) && ( co +1 < g.colonnes ) && (lire(g.donnee_cases,(li - 1) * g.colonnes + co + 1) != mine)) 
        ecrire(g.donnee_cases,(li - 1) * g.colonnes + co + 1,lire(g.donnee_cases,(li - 1) * g.colonnes + co + 1) + 1) ;
    
    // même li que la mine,  co -1 
    if (( co -1 > -1) && (lire(g.donnee_cases,li * g.colonnes + co - 1) != mine)) 
        ecrire(g.donnee_cases,li * g.colonnes + co - 1,lire(g.donnee_cases,li * g.colonnes + co - 1) + 1);
                                    
    // même li que la mine, co +1 
    if (( co +1 < g.colonnes ) && (lire(g.donnee_cases,li * g.colonnes + co + 1) != mine)) 
        ecrire(g.donnee_cases,li * g.colonnes + co + 1,lire(g.donnee_cases,li * g.colonnes + co + 1) +1);    

    // li + 1, co -1     
    if (( li + 1 < g.lignes ) && ( co -1 > -1) && (lire(g.donnee_cases,(li + 1) * g.colonnes + co - 1) != mine)) 
        ecrire(g.donnee_cases,(li + 1) * g.colonnes + co - 1,lire(g.donnee_cases,(li + 1) * g.colonnes + co - 1) +1);
    
                       
    // li + 1, même co que la mine  
    if (( li + 1 < g.lignes ) && (lire(g.donnee_cases,(li + 1) * g.colonnes + co) != mine)) 
        ecrire(g.donnee_cases,(li + 1) * g.colonnes + co,lire(g.donnee_cases,(li + 1) * g.colonnes + co) +1);

    // li + 1,  co +1 
    if (( li + 1 < g.lignes ) && ( co +1 < g.colonnes ) && (lire(g.donnee_cases,(li + 1) * g.colonnes + co + 1) != mine)) 
        ecrire(g.donnee_cases,(li + 1) * g.colonnes + co + 1,lire(g.donnee_cases,(li + 1) * g.colonnes + co + 1) +1);
} 

/**
 * @brief à partir d’un problème et d’un historique de coups, produire une grille
 * @param [in] affiche si true afficher la grille sinon ne pas l'afficher
 * @return etat_partie voir enum etat_jeux { en_cours, perdu, gagne }
 */
int produire_grille(bool affiche ){
    grille grl;
    string coup;
    int etat_partie;

    cin >> grl.lignes >> grl.colonnes >> grl.mines;
    intialiser_grille(grl);
    for (int i =0;i<grl.mines;i++){
        int idx_mine;
        cin >> idx_mine;
        ajouter_mine(grl, idx_mine);
     }
    int nb_coups;
            
    cin >> nb_coups;
    for(int cp=0;cp<nb_coups;cp++){
        cin >> coup;
        if ( grl.partie_terminee == en_cours)
            jouer_coup(grl,coup);
    }
    if (affiche)        
        afficher_grille(grl);
    
    etat_partie = grl.partie_terminee;
    // liberer les memoire allouées dynamiquement
    detruire(grl.donnee_cases);
    detruire(grl.etat_cases); 
    return etat_partie; 
}

/**
 * @brief afficher la grille
 * de capacité (capa) extensible par pas d'extension (p)
 * @see detruire, pour sa désallocation en fin d'utilisation 
 * @param [in] g : grille à afficher
 */
void afficher_grille (const grille& g){
     cout << g.lignes << " " << g.colonnes << endl;
    for (int l=0; l<g.lignes; l++){
        for (int c=0; c<g.colonnes; c++)
            cout << " ___";
        cout << "" << endl ;
        for (int c=0; c<g.colonnes; c++){
            if((lire(g.donnee_cases,l * g.colonnes + c) == mine) && (g.partie_terminee != en_cours)){    // cas avec mine
                    cout << "| " << "m" << " ";
                } else {
                            if (lire(g.etat_cases,l * g.colonnes + c) == masque){    // case masquée
                                cout << "| . ";
                            } 
                            if (lire(g.etat_cases,l * g.colonnes + c) == demasque){    // case démasquée
                                if (lire(g.donnee_cases,l * g.colonnes + c) == vide)     // case vide
                                    cout << "| " << " " << " ";
                                else cout << "| " << lire(g.donnee_cases,l * g.colonnes + c)  << " ";
                            }
                            if (lire(g.etat_cases,l * g.colonnes + c) == marque )    // case marquée
                                cout << "| X ";
                        }
        }
        cout  << "|" << endl ;
    }            
            
    for (int c=0; c<g.colonnes; c++)
            cout << " ___";
    cout << endl;     
    
}

/**
 * @brief rendre visible le voisinage d'une case si case vide
 * @param[in,out] g : grille
 * @param [in]  : position index de la case à traiter
 */

void rendre_visible_voisinage(grille& g,int position){
// A faire
}

/**
 * @brief Jouer coup
 * @param[in,out] g : grille
 * @param [in] coup : coup à jouer sous forme de M ou D suivi
 *                    de la position de la cses à traiter
 */
bool jouer_coup(grille& g, string coup){
    
    int idx_case = stoi(coup.substr(1,coup.size()));
    int li   = idx_case / g.colonnes;
    int co = idx_case % g.colonnes;
    // cas d'un coup de type marquer
    if (coup[0] == 'M'){
        if(lire(g.etat_cases,idx_case) == masque)   // case non  masquée    
            ecrire(g.etat_cases,idx_case,marque);   //  taguer case comme marquée
            if( lire(g.donnee_cases,idx_case) != mine ){   //  la case marquée n estpas une mine
                g.partie_terminee = perdu;                // 2 -> partie perdue
                return false;
            }
    }
    // cas d'un coup de type démasquer
    if (coup[0] == 'D'){
        if (lire(g.donnee_cases,idx_case) == mine ) {  // mine démasquée --> partie perdu 
            g.partie_terminee = perdu;          // partie perdue
            return false;
        }
        ecrire(g.etat_cases,idx_case,demasque);
        if (lire(g.donnee_cases,idx_case) == vide){    // case vide
        // On traite les cases adjacentes à la mine
        // li - 1, co -1     
        if (( li -1 > -1 ) && ( co -1 > -1) && (lire(g.donnee_cases,(li - 1) * g.colonnes + (co - 1)) > mine) && (lire(g.etat_cases,(li - 1) * g.colonnes + (co - 1)) != marque)) 
            ecrire(g.etat_cases,(li - 1) * g.colonnes + (co - 1),demasque);
               
        // li - 1, même co que la mine 
        if (( li -1 > -1 ) && (lire(g.donnee_cases,(li - 1) * g.colonnes + co) > mine) && (lire(g.etat_cases,(li - 1) * g.colonnes + co) !=marque)) 
            ecrire(g.etat_cases,(li - 1) * g.colonnes + co,demasque);
                    
        // li - 1 co +1 
        if (( li -1 > -1 ) && ( co + 1 < g.colonnes ) && (lire(g.donnee_cases,(li - 1) * g.colonnes + co + 1) > mine) && (lire(g.etat_cases,(li - 1) * g.colonnes + co + 1) !=marque )) 
            ecrire(g.etat_cases,(li - 1) * g.colonnes + co + 1,demasque);

        // même li que la mine,  co -1 
        if (( co -1 > -1) && (lire(g.donnee_cases,li * g.colonnes + co - 1) > mine ) && (lire(g.etat_cases,li * g.colonnes + co - 1) != marque)) 
            ecrire(g.etat_cases,li * g.colonnes + co - 1,demasque);
                                    
        // même li que la mine, co +1 
        if (( co +1 < g.colonnes ) && (lire(g.donnee_cases,li * g.colonnes + co + 1) > mine) && (lire(g.etat_cases,li * g.colonnes + co + 1) != marque)) 
            ecrire(g.etat_cases,li * g.colonnes + co + 1,demasque);

        // li + 1, co -1     
        if (( li + 1 < g.lignes ) && ( co - 1 > -1) && (lire(g.donnee_cases,(li + 1) * g.colonnes + co - 1) > mine ) && (lire(g.etat_cases,(li + 1) * g.colonnes + co - 1) !=marque)) 
            ecrire(g.etat_cases,(li + 1) * g.colonnes + co - 1,demasque);
        
        // li + 1, même co que la mine 
        if (( li + 1 < g.lignes ) && (lire(g.donnee_cases,(li + 1) * g.colonnes + co) > mine) && (lire(g.etat_cases,(li + 1) * g.colonnes + co) !=marque )) 
            ecrire(g.etat_cases,(li + 1) * g.colonnes + co,demasque);
                    
        // li + 1,  co +1 
        if (( li + 1 < g.lignes ) && ( co +1 < g.colonnes ) && (lire(g.donnee_cases,(li + 1) * g.colonnes + co + 1) > mine) && (lire(g.etat_cases,(li + 1) * g.colonnes + co + 1) !=marque)) 
            ecrire(g.etat_cases,(li + 1) * g.colonnes+co + 1,demasque);
        }
    }
    
    int nb_case_masquees=0;
    // calcul du nombre de cases demasquées, 
    for(int i=0;i<g.lignes * g.colonnes;i++){
        if (lire(g.etat_cases,i) == demasque )
            nb_case_masquees++;
    }
    
    if((g.lignes * g.colonnes) == (nb_case_masquees + g.mines)){
        g.partie_terminee = gagne;     // partie gagnée
    }
    return true;
}

