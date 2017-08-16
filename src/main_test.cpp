#include <vector>
#include <string>
#include <iostream>

#include "graph.hpp"

Graph* graphe;


// Interface entre le graphe et l'utilisateur
bool	writeCout(void) {
        cout << "Votre Commande : ";

	// On récupère l'evenement str
	string str;
        cin >> str;
	// Si evenement fait
	if(graphe->submit(str)) {
		cout << "\tEvenement : " << str << " fait !" << endl;
		// Si on arrive à la fin
		if(graphe->actuelState == graphe->finalState) {return false;}
	} 
	// Si evenement non fait
	else {
		// Soit demande de fin
		if(str == "q") {return false;}
		// Soit erreur
		else {cout << "\tIl n'y a pas d'evenement : " << str << " !" << endl;}
	}
	cout << endl;
	return true;
}


// Exemple de fonction doA utilisateur
void	doA(void) {
	cout << "\t\t\tFonction doA executée !!" << endl;
}


// Exemple de fonction doB utilisateur
void    doB(void) {
        cout << "\t\t\tFonction doB executée !!" << endl;
}


// Exemple de fonction doC utilisateur
void    doC(void) {
        cout << "\t\t\tFonction doC executée !!" << endl;
}


// Exemple de fonction doD utilisateur
void    doD(void) {
        cout << "\t\t\tFonction doD executée !!" << endl;
}


// Exemple de fonction doE utilisateur
void    doE(void) {
        cout << "\t\t\tFonction doE executée !!" << endl;
}


// Ajout des fonctions
void	addFunctions(void) {
	void (*pointeurSurFonction)(void);
 
  	pointeurSurFonction = doA;
	graphe->registerGraph("doA", pointeurSurFonction);
        pointeurSurFonction = doB;
        graphe->registerGraph("doB", pointeurSurFonction);
        pointeurSurFonction = doC;
        graphe->registerGraph("doC", pointeurSurFonction);
        pointeurSurFonction = doD;
        graphe->registerGraph("doD", pointeurSurFonction);
        pointeurSurFonction = doE;
        graphe->registerGraph("doE", pointeurSurFonction);

}


// Programme de l'utilisateur
int     main() {
	// Créer le graphe
	graphe = new Graph();

	// Ajout des fonctions
	addFunctions();

	// Début du graphe
	graphe->begin();
	// Interaction
        while(writeCout()){}
	// Fin du graphe
	graphe->end();	

	// Destruction du graphe
	delete graphe;

	return 0;
}
