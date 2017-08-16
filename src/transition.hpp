#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include <iostream>
#include <vector>

#include "action.hpp"
class State;

using namespace std;

/****
*
* Class représentant les transitions entre deux états
*
****/
class Transition {
	public : 
		// Evenement déclancheur
                string event;
		// Etat cible
                State* state;
		// Nom de l'Etat cible		
		string target;
		// Type de transition (external ou internal)
		string type;

		// Actions déclanchées par la transition
		vector<Action*> actions;		

		// Constructeur
		Transition(string e, string ty, string ta) : event(e), type(ty), target(ta) {};

		// Recherche l'état cible et se l'associe
		void findState(vector<State*> v);
		// S'ajoute une action
		void addAction(Action* a);

		// Destructeur
		~Transition() {
			for(int i = 0; i < actions.size(); i++) {
				delete actions[i];
			}
		};
};

#endif
