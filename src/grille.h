/**
 * @file grille.h
 * Projet création du démineur
 * @authors Chaimae EL MATTARI, Cedric TANGHE 
 * @version 1.0 - 09/01/2022
 * @brief 
 * 
 */

#ifndef _GRILLE_
#define _GRILLE_
#include<iostream>
#include<cstdlib>
#include <random>
#include <ctime>
#include <cassert>
#include <string>
#include "ConteneurTDE.h"
#include "probleme.h"

using namespace std;

enum etat_jeux { en_cours, perdu, gagne };
enum etat_case { masque, demasque, marque };
enum contenu_case { mine=-1, vide};

struct grille {
    unsigned int lignes;
    unsigned int colonnes;
    unsigned int mines;
    unsigned int partie_terminee=en_cours;  // 0 -> partie en cours, 1 -> partie perdue, 2 -> partie gangée 
    ConteneurTDE donnee_cases;              // -1 -> mine, 0 -> case vide, autre -> valeur > 0 
    ConteneurTDE etat_cases;                // 0 -> case masquée, 1 -> case démasquée, 2 -> case marquée 
};

void intialiser_grille(grille& g);
void ajouter_mine(grille& g, int idx_mine);
bool jouer_coup(grille& g, string coup);
void afficher_grille (const grille& g);
int  produire_grille(bool affiche );

#endif /*_GRILLE_*/


