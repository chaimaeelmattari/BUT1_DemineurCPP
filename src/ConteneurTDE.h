#ifndef CONTENEURTDE_H_
#define CONTENEURTDE_H_

using namespace std;

typedef int Item;

/** @brief Conteneur d'items alloués en mémoire dynamique
 *  de capacité extensible suivant un pas d'extension
 */ 
struct ConteneurTDE {
    unsigned int capacite; 	   // capacité du conteneur (>0)
	unsigned int pasExtension; // pas d'extension du conteneur (>0)
	Item* tab;				   // conteneur alloué en mémoire dynamique
};

void initialiser(ConteneurTDE& t, unsigned int c, unsigned int p);
Item lire(const ConteneurTDE& t, unsigned int i); 
void initialiser(ConteneurTDE& c, unsigned int capa, unsigned int p);
void detruire(ConteneurTDE& c);
void ecrire(ConteneurTDE& c, unsigned int i, const Item& it);
void ecrire(ConteneurTDE& c, unsigned int i, const Item& it);
bool contenir(ConteneurTDE& c, const Item& it);

#endif /*CONTENEURTDE_H_*/
