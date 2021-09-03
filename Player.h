#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

// Player data
class Player
{
	public:
		// PLayer's initial position on the map
		int start_pos;
		// Player's current position on the map
		int curr_pos;
		// Player's maximum health points
		int max_HP;
		// Player's current health points
		int curr_HP;
		// Max magic potion uses
		int max_potion;
		// Current magic potion uses
		int curr_potion;
		// Amount of money in player inventory
		int money;
		// Player status effect
		string status;
		// Current combat stance
		string curr_stance;
		// Previous combat stance
		string prev_stance;
		// Deflecting
		bool deflecting;
		// PLayer afflicted
		int afflicted;
		// Player resolve
		int resolve;
		// Player luck (affects criticals)
		int luck;
		// Bosses defeated
		int bosses_defeated;
		// Default constructor
		Player();
		// Drinks magic potion
		void magicPotion();
		// Prints player menu and returns action choice
		int printPlayerMenu();
		// Adds an item to player inventory
		void calcHP(int, int, int);
};

#endif