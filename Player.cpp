#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <vector>
#include "Player.h"
using namespace std;

Player::Player(){
	start_pos = 0;
	curr_pos = 0;
	max_HP = 100;
	curr_HP = 100;
	max_potion = 1;
	curr_potion = 1;
	status = "NONE";
	curr_stance = "Rooster";
	prev_stance = "Rooster";
	deflecting = false;
	afflicted = 0;
	resolve = 0;
	luck = 0;
	bosses_defeated = 0;
}

void Player::magicPotion(){
	if(curr_potion <= 0){
		cout << "\nOut of magic potion uses!" << endl;
		return;
	}
	cout << "\nThe magic potion restored " << (max_HP - curr_HP) << " health!" << endl;
	curr_HP = max_HP;
	if(status != "NONE"){
		cout << "PLAYER status was restored." << endl;
		status = "NONE";
	}
	curr_potion--;
	sleep(1);
}

int Player::printPlayerMenu(){
	// Set up answer for cin
	int out;
	// Player chooses from menu
	switch(bosses_defeated){
		default:
			do{
				sleep(1);
				cout << "- - - - - - - - - - - - - -" << endl;
				cout << "SELECT AN ACTION:" << endl;
				cout << "1. Rooster Stance" << endl;
				cout << "2. Carp    Stance" << endl;
				cout << "3. Beetle  Stance" << endl;
				cout << "4. Drink magic potion (" << curr_potion << "/" << max_potion << ")" << endl;
				cout << "- - - - - - - - - - - - - -" << endl;
				cout << endl;
				cin >> out;
				if(cin.fail()){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\033[31mERROR: Input not valid.\n\033[0m\n";
					return -1;
				}
				cout << endl;
				if(out == 1){
					cout << "ROOSTER STANCE:" << endl;
					cout << "1. Slash" << endl;
					cout << "2. ---" << endl;
					cout << "3. ---" << endl;
					cout << "4. ---" << endl;
					cout << "5. ---" << endl;
					cout << "6. Go back" << endl;
					cout << endl;
					cin >> out;
					if(cin.fail()){
						cin.clear();
					    cin.ignore(100, '\n');						
						cout << "\033[31mERROR: Input not valid.\n\033[0m\n";
						return -1;
					}
					if(out != 6){
						out = out - 1;
					}
				}
				else if(out == 2){
					cout << "CARP STANCE:" << endl;
					cout << "1. Pommel Strike" << endl;
					cout << "2. ---" << endl;
					cout << "3. ---" << endl;
					cout << "4. ---" << endl;
					cout << "5. ---" << endl;
					cout << "6. Go back" << endl;
					cout << endl;
					cin >> out;
					if(cin.fail()){
						cin.clear();
						cin.ignore(100, '\n');
						cout << "\033[31mERROR: Input not valid.\n\033[0m\n";
						return -1;
					}
					if(out != 6){
						out = 5 + out - 1;
					}
				}
				else if(out == 3){
					cout << "BEETLE STANCE:" << endl;
					cout << "1. Deflect" << endl;
					cout << "2. ---" << endl;
					cout << "3. ---" << endl;
					cout << "4. ---" << endl;
					cout << "5. ---" << endl;
					cout << "6. Go back" << endl;
					cout << endl;
					cin >> out;
					if(cin.fail()){
						cin.clear();
						cin.ignore(100, '\n');
						cout << "\033[31mERROR: Input not valid.\n\033[0m\n";
						return -1;
					}
					if(out != 6){
						out = 10 + out - 1;
					}
				}
				else if(out == 4){
					out = 44;
				}
				cout << endl;
			} while(out == 6);
			// If input is valid
			if(out == 0){
				curr_stance = "Rooster";
				return out;
			}
			if(out == 5){
				curr_stance = "Carp";
				return out;
			}
			if(out == 10){
				curr_stance = "Beetle";
				return out;
			}
			if(out == 44){
				return out;
			}
	}
	// Else, return -1 and do while loop again
	cout << "\033[31mERROR: Input not valid.\n\033[0m\n";
	return -1;
}

void Player::calcHP(int base_damage, int e_luck, int p_res){
	int damage, crit = round(e_luck * 5 + 10);
	if(crit > (rand()%100+1)){
		cout << "A critical hit!" << endl;
		damage = round(1.3 * base_damage);
	}
	else{
		damage = round((pow(base_damage, 2)) / (base_damage + p_res));
	}
	if(damage <= 0){
		damage = 1;
	}
	curr_HP = max(0, curr_HP - damage);
	cout << "PLAYER took " << damage << " damage!" << endl;
}