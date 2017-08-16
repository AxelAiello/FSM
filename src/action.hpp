#ifndef ACTION_HPP
#define ACTION_HPP

#include <iostream>
#include <vector>

using namespace std;

/*****
*
* Class représentant les actions comme "send" ou "raise"
*
*****/
class Action {
        public :
		// Evenement pour le quel l'action se declanche
                string event;
		// Type de l'evenement comme "send" ou "raise"
                string type;

		// Constructeur
                Action(string e, string ty) : event(e), type(ty) {};
};

#endif
