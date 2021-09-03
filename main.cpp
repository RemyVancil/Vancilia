#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "Skill.h"
using namespace std;


// INITIAL GAME GENERATION
// Generate Map, return vector of Map nodes
vector<Map> mapCreate(){
	// Declare map vector
	vector<Map> m;
	// Declare map file name
	string file_name = "world_map.csv";
	// Declare tokens to be used in reading
	string line, token;
	int map_token;
	// Open desired file
	ifstream fin(file_name);
	// Display error message and return if file opening fails
	if(!fin){
		cout << "\033[31mERROR: Map file not found.\n" << endl;
		return m;
	}
	// Read file
	while(getline(fin, line)){
		// Declare stream object and temp map object
		istringstream iss(line);
		Map temp;
		// READ FORMAT: <ID>, <biome>, <left>, <right>, <back>
		// Set id
		getline(iss, token, ',');
		temp.setID(stoi(token));
		// Set biome
		getline(iss, token, ',');
		temp.setBiome(stoi(token));
		// Set left
		getline(iss, token, ',');
		istringstream(token) >> map_token;
		temp.setLeft(map_token);
		// Set right
		getline(iss, token, ',');
		istringstream(token) >> map_token;
		temp.setRight(map_token);
		// Set back
		getline(iss, token);
		istringstream(token) >> map_token;
		temp.setBack(map_token);
		// Add newly-created object to vector
		if(iss){
			m.push_back(temp);
		}
	}
	// Return finished map vector
	return m;
}
// Generate vector of enemies
vector<Enemy> enemyCreate(){
	// Declare enemy vector
	vector<Enemy> e;
	// Declare enemy file name
	string file_name = "enemy_list.csv";
	// Declare strings to be used in reading
	string line, token;
	// Open desired file
	ifstream fin(file_name);
	// Display error message and return if file opening fails
	if(!fin){
		cout << "\033[31mERROR: Enemy file not found.\n" << endl;
		return e;
	}
	// Read file
	while(getline(fin, line)){
		// Declare stream object and temp map object
		istringstream iss(line);
		Enemy temp;
		vector<int> movepool;
		// READ FORMAT: <ID>, <biome>, <left>, <right>, <back>
		// Set id
		getline(iss, token, ',');
		temp.setID(stoi(token));
		// Set name
		getline(iss, token, ',');
		temp.setName(token);
		// Set max HP
		getline(iss, token, ',');
		temp.setMaxHP(stoi(token));
		// Set curr HP
		getline(iss, token, ',');
		temp.setCurrHP(stoi(token));
		// Set base resolve
		getline(iss, token, ',');
		temp.setResolve(stoi(token));
		// Set base luck
		getline(iss, token, ',');
		temp.setLuck(stoi(token));
		// Set status
		getline(iss, token, ',');
		temp.setStatus(token);
		// Set movepool
		for(int i = 0; i < 6; i++){
			getline(iss, token, ',');
			if(token != "-1"){
				movepool.push_back(stoi(token));
			}
		}
		temp.setSkills(movepool);
		// Set afflicted turn
		getline(iss, token);
		temp.setAfflicted(stoi(token));
		// Add newly-created object to vector
		if(iss){
			e.push_back(temp);
		}
	}
	// Return finished map vector
	return e;
}
// Generate vector of skills
vector<Skill> skillCreate(){
	// Declare skill vector
	vector<Skill> movepool;
	// Declare skill file name
	string file_name = "movepool.csv";
	// Declare strings to be used in reading
	string line, token;
	bool bool_token;
	// Open desired file
	ifstream fin(file_name);
	// Display error message and return if file opening fails
	if(!fin){
		cout << "\033[31mERROR: Skills file not found.\n" << endl;
		return movepool;
	}
	// Read file
	while(getline(fin, line)){
		// Declare stream object and temp map object
		istringstream iss(line);
		Skill temp;
		// READ FORMAT: <ID>, <name>
		// Set id
		getline(iss, token, ',');
		temp.setID(stoi(token));
		// Set name
		getline(iss, token, ',');
		temp.setName(token);
		// Set attack bool
		getline(iss, token);
		istringstream(token) >> bool_token;
		temp.setAttack(bool_token);
		if(iss){
			movepool.push_back(temp);
		}
	}
	// Return finished map vector
	return movepool;
}


// STATIC PRINT FUNCTIONS
// Print opening credits
void printOpening(){
}
// Print closing credits
void printClosing(int final_HP){
	// If game ended with player dead
	if(final_HP <= 0){
		cout << "G A M E   O V E R" << endl;
	}
	// If game ended with player alive
	else{

	}
}

// CONDITION FUNCTIONS
// Print status effect with colors
void statusPrint(string status){
	cout << "Status:";
	// Stun = Yellow
	if(status == "Stun"){
		cout << "\033[93m Stun\033[0m" << endl;
		return;
	}
	// Burn = Bright Red
	else if(status == "Burn"){
		cout << "\033[91m Burn\033[0m" << endl;
		return;
	}
	// Bleed = Red
	else if(status == "Bleed"){
		cout << "\033[31m Bleed\033[0m" << endl;
		return;
	}
	// Frozen = Cyan
	else if(status == "Frozen"){
		cout << "\033[36m Frozen\033[0m" << endl;
		return;
	}
	// Oil = Black
	else if(status == "Oil"){
		cout << "\033[34m Oil\033[0m" << endl;
		return;
	}
	// Poison = Green
	else if(status == "Poison"){
		cout << "\033[32m Poison\033[0m" << endl;
		return;
	}
	// Terror = Magenta
	else if(status == "Terror"){
		cout << "\033[35m Terror\033[0m" << endl;
		return;
	}
}
// Determine effect of status at end of turn
void statusEffect(Player &p, Enemy &e){
	// Check player effect, if applicable
	if(p.status != "NONE"){
		cout << endl;
		// If poison
		if(p.status == "Poison"){
			// Calculate poison damage
			int poison_dmg = round(p.max_HP*0.03);
			cout << "\033[32mPLAYER lost " << poison_dmg << " HP due to poison.\033[0m" << endl;
			// Poison does damage, always survive with 1 health
			p.curr_HP = max(1, p.curr_HP - poison_dmg);
			// If player has more than 1 HP
			if(p.curr_HP > 1){
				p.afflicted = max(0, p.afflicted - 1);
				// Chance to recover from poison
				if(p.afflicted <= 0){
					if(rand() % 2 == 0){
						cout << "PLAYER recovered from poison!" << endl;
						p.status = "NONE";
					}
				}
			}
			// If player is at 1 HP
			else{
				cout << "PLAYER recovered from poison!" << endl;
				p.afflicted = 0;
				p.status = "NONE";
			}
		}
		// If burn
		else if(p.status == "Burn"){
			int burn_dmg = round(p.max_HP*0.05);
			cout << "\033[91mPLAYER lost " << burn_dmg << " HP due to burn.\033[0m" << endl;
			p.curr_HP = max(0, p.curr_HP - burn_dmg);
			p.afflicted = max(0, p.afflicted - 1);
			if(p.afflicted <= 0){
				cout << "PLAYER recovered from burn!" << endl;
				p.status = "NONE";
			}
		}
		// If bleed
		else if(p.status == "Bleed"){
			p.afflicted = max(0, p.afflicted - 1);
			if(p.afflicted <= 0){
				p.curr_HP = max(0, p.curr_HP - 20);
				cout << "\033[31mTook 20 damage from bleed!\033[0m" << endl;
				if(p.curr_HP > 0){
					p.status = "NONE";
					cout << "PLAYER recovered from bleed!"<< endl;
				}
			}
			else{
				if(p.afflicted == 1){
					cout << "PLAYER will take damage from bleed in " << p.afflicted << " turn." << endl;
				}
				else{
					cout << "PLAYER will take damage from bleed in " << p.afflicted << " turns." << endl;
				}
			}
		}
		// If terror
		else if(p.status == "Terror"){
			if(p.resolve > 0){
				cout << "\033[35mPLAYER lost resolve due to terror!\033[0m" << endl;
				p.resolve = max(0, p.resolve - 1);
			}
		}
		// Check if PLAYER is still alive
		if(p.curr_HP <= 0){
			return;
		}
	}
	// Check enemy effect, if applicable
	if(e.getStatus() != "NONE"){
		cout << endl;
		// If stun
		if(e.getStatus() == "Stun"){
			e.setAfflicted(e.getAfflicted() - 1);
			if(e.getAfflicted() == 0){
				cout << e.getName() << " recovered from stun!" << endl;
				e.setStatus("NONE");
				e.setResolve(e.getResolve() + 1);
			}
		}
		// If burn
		else if(e.getStatus() == "Burn"){
			int burn_dmg = 5;
			cout << "\033[91m" << e.getName() << " lost " << burn_dmg << " HP due to burn.\033[0m" << endl;
			e.setCurrHP(max(0, e.getCurrHP() - burn_dmg));
			e.setAfflicted(max(0, e.getAfflicted() - 1));
			if(e.getAfflicted() <= 0){
				cout << e.getName() << " recovered from burn!" << endl;
				e.setStatus("NONE");
			}
		}
	}
	cout << endl;
}


// MAP TRAVERSAL
// Print special path descriptions
void specialPath(int node_ID){
	switch(node_ID){
		case 5:
			cout << "\nTo your left, the main road continues." << endl;
			cout << "To your right, animal tracks lead deeper into the woods..." << endl;
			break;
		case 6:
			cout << "\nThere's a clearing up ahead." << endl;
			cout << "In its center, a figure watches your approach..." << endl;
			break;
		case 11:
			cout << "\nTo your left, the path drops into a gemstone tunnel..." << endl;
			cout << "To your right, the path snakes past bubbling tar pits..." << endl;
			break;
		case 13:
			cout << "\nThere's a hot spring up ahead." << endl;
			break;
	}
}
// Print menu for overworld actions
int printActionMenu(int l, int r, int b){
	// Set up answer for cin
	int out;
	// Set up vector
	vector<int> is_valid;
	// Display action menu
	cout << "\nSELECT AN ACTION:" << endl;
	// If left is valid
	if(l != -1){
		// If right is valid
		if(r != -1){
			cout << "1. Go left" << endl;
			cout << "2. Go right" << endl;
			is_valid.push_back(1);
			is_valid.push_back(2);
		}
		// If right is not valid
		else{
			cout << "1. Go straight" << endl;
			cout << "2. ---" << endl;
			is_valid.push_back(1);
		}
	}
	// If left is not valid
	else{
		cout << "1. ---" << endl;
		cout << "2. ---" << endl;
	}
	// If down is valid
	if(b != -1){
		cout << "3. Go down" << endl;
		is_valid.push_back(3);
	}
	// If down is not valid
	else{
		cout << "3. ---" << endl;
	}
	// Print other two options
	cout << "4. View player status" << endl;
	is_valid.push_back(4);
	cout << "5. Use magic potion" << endl;
	is_valid.push_back(5);
	cout << "6. Change stance\n" << endl;
	is_valid.push_back(6);
	// Player chooses from menu
	cin >> out;
	// Check if int
	if(cin.fail()){
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\033[31mERROR: Input not valid.\n\033[0m";
		return -1;
	}
	// Check validity of input and return
	for(int i = 0; i < is_valid.size(); i++){
		if(out == is_valid[i]){
			return out;
		}
	}
	//Else, return -1 and do while loop again
	cout << "\033[31mERROR: Input not valid.\n\033[0m";
	return -1;
}
// Access menus and choose path
int path(vector<Map> &m, Player &p){
	// Cin to be checked for action / validity
	int ans;

	// Check what paths are available
	int node_left = m[p.curr_pos].getLeft();
	int node_right = m[p.curr_pos].getRight();
	int node_back = m[p.curr_pos].getBack();

	// Call left special if available
	if(node_left != -1){
		//cout << "Left biome: " << m[node_left].get_biome() << endl;
		specialPath(node_left);
	}
	// Call right special if available
	if(node_right != -1){
		//cout << "Right biome: " << m[node_right].get_biome() << endl;
		specialPath(node_right);
	}
	// Call back special if available
	if(node_back != -1){
		//cout << "Back biome: " << m[node_back].get_biome() << endl;
		specialPath(node_back);
	}

	do{
		do {
			// Display action menu
			ans = printActionMenu(node_left, node_right, node_back);
		} while(ans == -1);

		// Perform actions based on player selection
		switch(ans){
			case 1:
				return node_left;
			case 2:
				return node_right;
			case 3:
				return node_back;
			case 4:
				// char info()
				cout << "\nPLAYER" << endl;
				cout << "HP: " << p.curr_HP << " / " << p.max_HP << endl;
				cout << "Stance: " << p.curr_stance << endl;
				cout << "Resolve: " << p.resolve << " / 5" << endl;
				cout << "Luck: " << p.luck << endl;
				if(p.status != "NONE"){
					statusPrint(p.status);
				}
				cout << endl;
				break;
			case 5:
				// Magic potion
				p.magicPotion();
				break;
			case 6:
				// Change stance
				cout << "\nCURRENT STANCE: " << p.curr_stance << endl;
				cout << "NEW STANCE: " << endl;
				cout << "1. Rooster" << endl;
				cout << "2. Carp" << endl;
				cout << "3. Beetle" << endl;
				cin >> ans;
				if(cin.fail()){
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\033[31mERROR: Input not valid.\n\033[0m";
				}
				else{
					cout << endl;
					switch(ans){
						case 1:
							p.curr_stance = "Rooster";
							p.prev_stance = p.curr_stance;
							break;
						case 2:
							p.curr_stance = "Carp";
							p.prev_stance = p.curr_stance;
							break;
						case 3:
							p.curr_stance = "Beetle";
							p.prev_stance = p.curr_stance;
							break;
					}
				}
				ans = 6;
		}
	} while(ans >=4 && ans <= 6);
	return -1;
}


// COMBAT FUNCTIONS
// Retrieves a random biome-based enemy
int getEnemy(int biome){
	int r;
	cout << endl;
	switch(biome){
		// Forest
		case 2:
			return rand() % 3;
		// Deep Forest
		case 3:
			return 3;
		// Forest Boss
		case 4:
			cout << "BOSS – ";
			return 4;
		// Mountain
		case 5:
			return rand() % 4 + 5;
		// Gem Mountain
		case 6:
			return 9;
		// Tar Mountain
		case 7:
			return 10;
		// Mountain Boss
		case 8:
			cout << "BOSS – ";
			return 11;
		// Invalid biome call
		default:
			return -1;
	}
}
// Marks current spot as checkpoint
void setCheckpoint(Player &p){
	p.bosses_defeated += 1;
	p.curr_HP = p.max_HP;
	p.max_potion = p.bosses_defeated + 1;
	p.curr_potion = p.max_potion;
	p.status = "NONE";
	p.prev_stance = p.curr_stance;
	p.afflicted = 0;
	p.resolve = 0;
	p.luck = 0;
	// Sets current spot as new starting point
	p.start_pos = p.curr_pos;
}
// Resets hero to checkpoint
void loadCheckpoint(Player &p){
	p.curr_HP = p.max_HP;
	p.curr_potion = p.max_potion;
	p.status = "NONE";
	p.prev_stance = p.curr_stance;
	p.afflicted = 0;
	p.resolve = 0;
	p.luck = 0;
	// Moves player back to starting pos
	p.curr_pos = p.start_pos;
}
// Bonus function
void reward(Player &p, int enemy_ID){
	switch(enemy_ID){
		case 3:
			p.resolve = 5;
			return;
		case 4:
			setCheckpoint(p);
			return;
		case 9:
			p.luck = 5;
			return;
		case 10:
			p.curr_HP = max(p.max_HP, p.curr_HP + 30);
			return;
		case 11:
			setCheckpoint(p);
			return;
		default:
			return;
	}
}
// Combat loop function
void combat(Player &p, Enemy e, vector<Skill> movepool){
	cout << e.getName() << "\033[0m attacked!\n" << endl;
	sleep(1);
	int turn = 1, ans;
	// Reset enemy defaults
	// enemyDefaults();
	do{
		sleep(1);
		p.prev_stance = p.curr_stance;
		p.deflecting = false;

		// Display start-of-turn stats
		cout << "\n––– TURN " << turn << " –––––––––––––" << endl;
		// Print player status
		cout << "PLAYER" << endl;
		cout << "HP: " << p.curr_HP << " / " << p.max_HP << endl;
		cout << "Stance: " << p.curr_stance << endl;
		cout << "Resolve: " << p.resolve << " / 5" << endl;
		cout << "Luck: " << p.luck << endl;
		if(p.status != "NONE"){
			statusPrint(p.status);
		}
		cout << endl;

		// Print enemy status
		cout << e.getName() << endl;
		cout << "HP: " << e.getCurrHP() << " / " << e.getMaxHP() << endl;
		cout << "Resolve: " << e.getResolve() << " / 5" << endl;
		cout << "Luck: " << e.getLuck() << endl;
		if(e.getStatus() != "NONE"){
			statusPrint(e.getStatus());
		}
		cout << endl;

		// Player turn
		if(p.status != "Stun"){
			do {
				ans = p.printPlayerMenu();
			} while(ans == -1);
			// If player selected an item
			if(ans == 44){
				cout << "PLAYER used the magic potion!" << endl;
				p.magicPotion();
			}
			// If player selected an attack
			else{
				movepool[ans].skillEffect(p, e, 'p');
			}
		}
		else{
			cout << "\033[93mPLAYER was stunned and could not attack!\033[0m" << endl;
		}
		// Check game conditon
		if(e.getCurrHP() <= 0){
			cout << '\n' << e.getName() << " was defeated!" << endl;
			cout << "\n–––––––––––––––––––––––\n" << endl;
			break;
		}
		sleep(1);
		// Enemy turn
		if(e.getStatus() != "Stun"){
			ans = e.AI_action(p.curr_HP, p.status);
			movepool[ans].skillEffect(p, e, 'e');
		}
		else{
			cout << "\033[93m" << e.getName() << " was stunned and could not attack!\033[0m" << endl;
		}
		if(p.curr_HP <= 0){
			cout << "\nPLAYER was defeated!" << endl;
			cout << "\n–––––––––––––––––––––––\n" << endl;
			break;
		}
		// Apply after turn effects
		if(p.status != "NONE" || e.getStatus() != "NONE"){
			statusEffect(p, e);
		}
		// If player died to after turn effects
		if(p.curr_HP <= 0){
			cout << "\nPLAYER was defeated!" << endl;
			cout << "\n–––––––––––––––––––––––\n" << endl;
			break;
		}
		// If enemy died to after turn effects
		if(e.getCurrHP() <= 0){
			cout << '\n' << e.getName() << " was defeated!" << endl;
			cout << "\n–––––––––––––––––––––––\n" << endl;
			break;
		}
		p.prev_stance = p.curr_stance;
		turn++;
		// End turn
		cout << "–––––––––––––––––––––––\n" << endl;
	} while(turn < INT_MAX);
	if(p.curr_HP > 0){
		// If player status is type to go away post-combat, set to none
		if(p.status == "Frozen" || p.status == "Bleed" || p.status == "Stun" || p.status == "Terror"){
			p.afflicted = 0;
			p.status = "NONE";
		}
		// Receive bonus
		reward(p, e.getID());
	}
}
// Determines whether game will continue
int gameContinue(){
	int out = -1;
	do{
		cout << "\nCONTINUE?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No\n" << endl;
		cin >> out;
		cout << endl;
		if(cin.fail()){
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\033[31mERROR: Input not valid.\n\033[0m\n";
			out = -1;
		}
		if(out != 1 && out != 2){
			out = -1;
		}
	} while(out == -1);
	return out;
}


// MAIN DRIVER
int main(){
	// Initialize default values
	srand(time(NULL));
	Player p;
	int biome, enemy_ID;

	// Call map generation function
	vector<Map> world_map = mapCreate();
	vector<Enemy> e = enemyCreate();
	vector<Skill> movepool = skillCreate();

	// If vector is empty (error thrown)
	if(world_map.empty() || e.empty() || movepool.empty()){
		return 1;
	}

	// Print opening screen
	printOpening();

	// MAIN GAMEPLAY LOOP
	do{
		// Select player's next action and update map location
		p.curr_pos = path(world_map, p);
		// If error, break
		if(p.curr_pos == -1){
			return 1;
		}
		cout << "\nCurrent position: " << p.curr_pos << endl;
		// Check if safe zone
		biome = world_map[p.curr_pos].getBiome();
		if(biome == 0){
			setCheckpoint(p);
		}
		else{
			// If not safe, retrieve enemy
			enemy_ID = getEnemy(biome);
			// If enemy retrieval fails
			if(enemy_ID == -1){
				cout << "\033[31mERROR: Enemy ID not found.\n" << endl;
				return 1;
			}
			// If enemy retrieval succeeds, call combat func
			combat(p, e[enemy_ID], movepool);
			// If combat ends with player dead, end game
			if(p.curr_HP <= 0){
				if(gameContinue() == 1){
					cout << "\nReturned to most recent checkpoint..." << endl;
					loadCheckpoint(p);
				}
				else{
					break;
				}
			}
		}
	} while(p.bosses_defeated < 4);

	// Print closing screen
	printClosing(p.curr_HP);
	return 0;
}