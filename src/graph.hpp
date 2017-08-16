#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "state.hpp"

using namespace std;

typedef void (*F)(void);

/*****
*
* Class représentant un Graph
*
*****/
class Graph {
	public :
		// Liste des Etat 
		vector<State*> vStates;
		// Etat initial
		State* initialState = nullptr;
		// Etat actuel
		State* actuelState = nullptr;
		// Etat final
		State* finalState = nullptr;
		// Fonctions associées à leur évenement
		map<string, F> mapFonction;
		

		// Constructeur
		Graph();

		// Ajoute la fonction avec son evenement		
		void registerGraph(string event, F f) {mapFonction[event] = f;};

		// Début du Graphe
		void begin(void) {
			if(actuelState == initialState && initialState != nullptr) {
				vector<string> q_begin;
				cout << "\t\tAction(s) onentry de l'état " << actuelState->name << endl;
                                // Faire les fonctions onentry s'il y en a 
                                executeActions(actuelState->onentry, q_begin);
                                cout << "\tRentre dans l'état " << actuelState->name << endl;
                                // Si l'état n'a pas de transition par evenement alors on le fait automatiquement
                                if(actuelState->transitions.size() == 1 && actuelState->transitions[0]->event == "") {
                                        q_begin.push_back("");
                                        cout << "\t\t\tDétection d'une transition sans evenement" << endl;
                                }
				cout << endl;
                                // On execute les actions garder en memoire
                                executeMemory(q_begin);
			}
		};

                // Fin du Graphe
                void end(void) {
                        if(actuelState == finalState && finalState != nullptr) {
				vector<string> q_end;
                         	cout << "\tSors de l'état " << actuelState->name << endl;
                                cout << "\t\tAction(s) onexit de l'état " << actuelState->name << endl;
                                // Faire les fonctions onexit s'il y en a 
                                executeActions(actuelState->onexit, q_end);
				cout << endl;
                                // On execute les actions garder en memoire
                                executeMemory(q_end);
			}
                };

		// Soumet un événement str
		bool submit(string str) {
			// Liste des evenements en sommeil
			vector<string> q;
			
			// On recherche l'événement dans les transitions de l'état actuel
        		for(int i = 0; i < actuelState->transitions.size(); i++) {
				// Si on a trouvé la transition
                		if(actuelState->transitions[i]->event == str) {
						cout << "\tSors de l'état " << actuelState->name << endl;
                                                
						cout << "\t\tAction(s) onexit de l'état " << actuelState->name << endl;
                                                // Faire les fonctions onexit s'il y en a 
                                                executeActions(actuelState->onexit, q);

                                                cout << "\t\tAction(s) de la transition" << endl;
						// Faire les fonctions de la transition s'il y en a 
						executeActions(actuelState->transitions[i]->actions, q);

                                                // Mise à jour de l'actuelState
                                                actuelState = actuelState->transitions[i]->state;

                                                cout << "\t\tAction(s) onentry de l'état " << actuelState->name << endl;
						// Faire les fonctions onentry s'il y en a 
						executeActions(actuelState->onentry, q);

						cout << "\tRentre dans l'état " << actuelState->name << endl;
						// Si l'état n'a pas de transition par evenement alors on le fait automatiquement
						if(actuelState->transitions.size() == 1 && actuelState->transitions[0]->event == "") {
							q.push_back("");
							cout << "\t\t\tDétection d'une transition sans evenement" << endl;
						}
						cout << endl;
						// On execute les actions garder en memoire
						executeMemory(q);
                        			return true;
                		}
        		}
			// Evenement str non trouvé
        		return false;
		};

		// Destructeur
		~Graph() {
			for(int i = 0; i < vStates.size(); i++) {delete vStates[i];}
		};

	private : 
                // Execute les fonctions données si elles sont renseignées
                void executeActions(vector<Action*> v, vector<string>& q) {
                        map<string,F>::iterator it;
			// On parcourt les actions
                        for(int k = 0; k < v.size(); k++) {
                                it = mapFonction.find(v[k]->event);
				// Si on trouve la fonction associée on l'execute
                                if(it != mapFonction.end()) {mapFonction[v[k]->event]();}
				// Sinon c'est peut être un evenement
				else {
					q.push_back(v[k]->event);
					cout << "\t\t\tDétection d'un evenement : " << v[k]->event << endl;
				}
                        }
                };

		// On execute les actions garder en mémoire
		void executeMemory(vector<string> q) {
                        for(int k = 0; k < q.size(); k++) {
                               if(q[k] == "") {cout << "Lancement de l'evenement vide stocké en mémoire" << endl;}
                               else {cout << "Lancement de l'evenement stocké en mémoire : " << q[k] << endl;}
                               submit(q[k]);
                        }
		}
};

#endif
