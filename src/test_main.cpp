#include <vector>
#include <string>
#include <iostream>
#include "state.hpp"

using namespace std;

int 	main() {
	vector<State*> vStates;
	vector<Transition*> vTransitions;
	State* actuelState;

	vStates.push_back(new State("Reset"));
	vTransitions.push_back(new Transition("Stop", "external", "Start"));
		vStates[vStates.size() - 1]->addTransitions(vTransitions[vTransitions.size() - 1]);

	vStates.push_back(new State("Stop"));
	vTransitions.push_back(new Transition("Stop", "external", "Reset"));
		vStates[vStates.size() - 1]->addTransitions(vTransitions[vTransitions.size() - 1]);

	vStates.push_back(new State("Start"));
	vTransitions.push_back(new Transition("Stop", "external", "Stop"));
		vStates[vStates.size() - 1]->addTransitions(vTransitions[vTransitions.size() - 1]);
	vTransitions.push_back(new Transition("Pause", "external", "Pause"));
		vStates[vStates.size() - 1]->addTransitions(vTransitions[vTransitions.size() - 1]);
	vTransitions.push_back(new Transition("septms", "external", "Start"));
		vStates[vStates.size() - 1]->addTransitions(vTransitions[vTransitions.size() - 1]);

	vStates.push_back(new State("Pause"));
	vTransitions.push_back(new Transition("Stop", "external", "Stop"));
		vStates[vStates.size() - 1]->addTransitions(vTransitions[vTransitions.size() - 1]);
	vTransitions.push_back(new Transition("Pause", "external", "Start"));
		vStates[vStates.size() - 1]->addTransitions(vTransitions[vTransitions.size() - 1]);

	for(int i = 0; i < vTransitions.size(); i++) {
		 vTransitions[i]->findState(vStates);
	}

	actuelState = vStates[0];


	while(true) {
		cout << "Etat actuel : " << actuelState->name << endl;
		cout << "Votre Commande :";
		string str;
		cin >> str;
		for(int i = 0; i < actuelState->transitions.size(); i++) {
			if(actuelState->transitions[i]->event == str) {
				cout << "Evenement : " << actuelState->transitions[i]->event << " fait !" << endl;
				actuelState = actuelState->transitions[i]->state;
			}
		}
		cout << endl;
	}
}
