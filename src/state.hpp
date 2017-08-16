#ifndef STATE_HPP
#define STATE_HPP

#include "transition.hpp"
#include <vector>

/*****
*
* Class représentant un Etat
*
*****/
class State {
	public :
		// Nom de l'Etat
		string name;
		// Transition à partir de cet Etat
		vector<Transition*> transitions;
		// Actions onentry
		vector<Action*> onentry;
		// Actions onexit
		vector<Action*> onexit;

		// Constructeur
		State(string n) : name(n) {};
		// S'ajoute une transition
		void addTransitions(Transition* l) {transitions.push_back(l);};
		// S'ajoute une action onentry
		void addOnentry(Action* a) {onentry.push_back(a);};
		// Sajoute une action onexit
		void addOnexit(Action* a) {onexit.push_back(a);};

		// Destructeur
		~State() {
			for(int i = 0; i < transitions.size(); i++) {delete transitions[i];}
                        for(int i = 0; i < onentry.size(); i++) {delete onentry[i];}
                        for(int i = 0; i < onexit.size(); i++) {delete onexit[i];}
		};
	
};

#endif
