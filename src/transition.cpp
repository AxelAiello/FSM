#include "transition.hpp"
#include "state.hpp"

// Recherche l'état cible et se l'associe
void Transition::findState(vector<State*> v) {
	for(int i = 0; i < v.size(); i++) {
        	if(v[i]->name == target) {state = v[i];}
        }
};

// S'ajoute une action
void Transition::addAction(Action* a) {
	actions.push_back(a);
}

