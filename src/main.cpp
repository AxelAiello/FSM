// Bibliothèque pour la gestion du XML
#include "tinyxml.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

// Element actuel
TiXmlElement *elem;

using namespace std;

// Initialisation
bool 	initialisation(TiXmlDocument* doc, ofstream* fichier) { 
	// Verification si ok
	if(!doc->LoadFile()) {
    		cerr << "Erreur lors du chargement !" << endl;
    		cerr << "error #" << doc->ErrorId() << " : " << doc->ErrorDesc() << endl;
    		return false;
	}

	// Accède aux élèments du fichier
	TiXmlHandle docHandle(doc); // Protège mieux en cas d'erreur
	elem = docHandle.FirstChildElement("scxml").Element();
	// Verification si ok
	if(!elem) { 
		cerr << "Le nœud à atteindre n'existe pas !" << endl;
		return false;
	}

        // Verification si ok
        if(!fichier) {
                cerr << "Impossible d'ouvrir le fichier !" << endl;
                return false;
        }

	return true;
}


// Préparation à l'écriture et début
string  debutEcriture(void) {
        string str = "#include \"graph.hpp\"\n\n";

        str = str + "Graph::Graph(void) {\n";
        return str;
}


// Fin de l'ecriture
void    finEcriture(ofstream* fichier) {
        (*fichier) << "}\n";
        // Ferme le fichier
        fichier->close();
}

// Créer un objet état
void	creerState(ofstream* fichier, string name) {
        (*fichier) << "\tvStates.push_back(new State(\"" << name << "\"));"  << endl;
}

// Créer un objet transition associé au denrier état
void 	creerLink(ofstream* fichier, string e, string ty, string ta) {
        (*fichier) << "\t\t\tvStates[vStates.size() - 1]->addTransitions(new Transition(\"" << e << "\", \"" << ty << "\", \"" << ta << "\"));" << endl;
}

// Créer un objet action associé à la dernière transition du dernier état
void 	creerAction(ofstream* fichier, string event, string type) {
	(*fichier) << "\t\t\t\tvStates[vStates.size() - 1]->transitions[vStates[vStates.size() - 1]->transitions.size() - 1]->addAction(new Action(\"" << event << "\", \"" << type << "\"));" << endl << endl;
}

// Créer un objet action onentry associé au dernier état
void    creerActionOnentry(ofstream* fichier, string event, string type) {
        (*fichier) << "\t\t\t\tvStates[vStates.size() - 1]->addOnentry(new Action(\"" << event << "\", \"" << type << "\"));" << endl << endl;
}

// Créer un objet action onexit associé au dernier état
void    creerActionOnexit(ofstream* fichier, string event, string type) {
        (*fichier) << "\t\t\t\tvStates[vStates.size() - 1]->addOnexit(new Action(\"" << event << "\", \"" << type << "\"));" << endl << endl;
}

// Trouve l'état initial
void    initialState(string initial, string fin, ofstream* fichier) {
        // Si l'état initial n'est pas préciser
        if(initial == "") {
		if(fin == "") {(*fichier) << "\tinitialState = vStates[0];\n" << endl << endl;}
		else {(*fichier) << "\tinitialState = vStates[1];\n" << endl << endl;}
	}
        // S'il est préciser
        else {
                (*fichier) << "\tfor(int i = 0; i < vStates.size(); i++) {" << endl;
                (*fichier) << "\t\tif(vStates[i]->name == \"" << initial << "\") {initialState = vStates[i];}" << endl;
                (*fichier) << "\t}" << endl << endl;
        }
}

int	main(int argc, char** argv) {
	if(argc != 2) {
		cout << "\nErreur, vous devez préciser le document.scxml cible !\n" << endl;
		return 1;
	}
	TiXmlDocument doc(argv[1]);
	ofstream fichier("graph.cpp", ios::out | ios::trunc);

	// Préparation du fichier XML
	if(!initialisation(&doc, &fichier)) {return 1;}
	// Début du fichier
	fichier << debutEcriture();

	// Recherche l'etat initial
	string initial = "";
	if(elem->Attribute("initial")) {initial = elem->Attribute("initial");}

        // Recherche l'etat final
	string fin = "";
        if(elem->FirstChildElement("final")) {
                // Crée l'état
		fin = elem->FirstChildElement("final")->Attribute("id");
                creerState(&fichier, elem->FirstChildElement("final")->Attribute("id"));
                fichier << "\tfinalState = vStates[vStates.size() - 1];" << endl;
        }

        elem = elem->FirstChildElement("state");
        // Tant qu'on est pas à la fin du fichier
        while(elem){
                // Récupère l'état
                creerState(&fichier, elem->Attribute("id"));

		// Récupère les transitions
		TiXmlElement* elemFils = elem->FirstChildElement("transition");
		while(elemFils) {
			if(elemFils->Attribute("event")) {creerLink(&fichier, elemFils->Attribute("event"), elemFils->Attribute("type"), elemFils->Attribute("target"));}
			else {creerLink(&fichier, "", elemFils->Attribute("type"), elemFils->Attribute("target"));}
			// Récupère les raises
			TiXmlElement* elemPetitFils = elemFils->FirstChildElement("raise");
                        while(elemPetitFils) {
                                creerAction(&fichier, elemPetitFils->Attribute("event"), "raise");
				elemPetitFils = elemPetitFils->NextSiblingElement("raise");
                        }
                        elemFils = elemFils->NextSiblingElement("transition");
		}

                // Récupère les onentry
                elemFils = elem->FirstChildElement("onentry");
                while(elemFils) {
                        // Récupère les raises
                        TiXmlElement* elemPetitFils = elemFils->FirstChildElement("raise");
                        while(elemPetitFils) {
                                creerActionOnentry(&fichier, elemPetitFils->Attribute("event"), "raise");
                                elemPetitFils = elemPetitFils->NextSiblingElement("raise");
                        }
			elemFils = elemFils->NextSiblingElement("onentry");
                }

                // Récupère les onexit
                elemFils = elem->FirstChildElement("onexit");
                while(elemFils) {
                        // Récupère les raises
                        TiXmlElement* elemPetitFils = elemFils->FirstChildElement("raise");
                        while(elemPetitFils) {
                                creerActionOnexit(&fichier, elemPetitFils->Attribute("event"), "raise");
                                elemPetitFils = elemPetitFils->NextSiblingElement("raise");
                        }
			elemFils = elemFils->NextSiblingElement("onexit");
                }

		fichier << endl;
                // Va au prochain noeud 
                elem = elem->NextSiblingElement("state");
        }

	// Lie les états entre eux
	fichier << "\tfor(int i = 0; i < vStates.size(); i++) {\n\t\t for(int j = 0; j < vStates[i]->transitions.size(); j++) {\n\t\t\tvStates[i]->transitions[j]->findState(vStates);\n\t\t}\n\t}" << endl << endl;
	
	// State initiale
	initialState(initial, fin, &fichier);
        fichier << "\tactuelState = initialState;\n" << endl;
	
	// Fin Ecriture et Lecture
        finEcriture(&fichier);

	return 0;
}
