#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Skill.h"
using namespace std;

Skill::Skill(){
	ID = -1;
	name = "NULL";
	attack = false;
}

int Skill::getID(){
	return ID;
}

string Skill::getName(){
	return name;
}

bool Skill::isAttack(){
	return attack;
}

void Skill::setID(int new_ID){
	ID = new_ID;
}

void Skill::setName(string new_name){
	name = new_name;
}

void Skill::setAttack(bool new_attack){
	attack = new_attack;
}

void Skill::stagger(Player &p){
	sleep(1);
	cout << "PLAYER was staggered!" << endl;
	int r = rand()%3;
	// Randomly set new stance
	if(r == 0){
		p.curr_stance = "Rooster";
	}
	else if(r == 1){
		p.curr_stance = "Carp";
	}
	else{
		p.curr_stance = "Beetle";
	}
	sleep(1);
	// Check if stance changed or not
	if(p.curr_stance == p.prev_stance){
		cout << "PLAYER maintained their stance." << endl;
	}
	else{
		cout << "PLAYER faltered! Stance was changed to " << p.curr_stance << "." << endl;
	}
	sleep(1);
}

void Skill::deflectSuccess(int hit, Player &p){
	int r = 1 + rand() % 100;
	int prob = round(100 * pow(0.85, hit - 1));
	if(r <= prob){
		cout << "Deflected!" << endl;
		p.resolve = min(5, p.resolve + 1);
	}
	else{
		cout << "Deflect failed!" << endl;
		p.resolve = max(0, p.resolve - 1);
		p.deflecting = false;
	}
}

void Skill::skillEffect(Player &p, Enemy &e, char flag){
	sleep(1);
	int stat_change, base_damage;
	// If skill user is player
	if(flag == 'p'){
		cout << "\nPLAYER used " << getName() << "!" << endl;
	}
	else if (flag == 'e'){
		if(p.curr_stance != p.prev_stance){
			e.setLuck(max(0, e.getLuck() + 2));
		}
		cout << '\n' << e.getName() << " used " << getName() << "!" << endl;
	}
	sleep(1);
	// Look up skill effect using switch
	switch(getID()){
		// ---- PLAYER SKILLS -----------
		// ROOSTER STANCE SKILLS
		// Slash
		case 0:
			p.curr_stance = "Rooster";
			base_damage = 25;
			e.calcHP(base_damage, p.luck, e.getResolve());
			break;
		case 1:
			p.curr_stance = "Rooster";
			base_damage = 10;
			e.calcHP(base_damage, p.luck, e.getResolve());
			if(e.getCurrHP() > 0){
				if(rand() % 2 == 0){
					cout << "\033[91m" << e.getName() << " was set ablaze!\033[0m" << endl;
					e.setStatus("Burn");
					e.setAfflicted(5);
				}
			}
			break;
		// CARP STANCE SKILLS
		// Pommel Strike
		case 5:
			p.curr_stance = "Carp";
			base_damage = 10;
			e.calcHP(base_damage, p.luck, e.getResolve());
			if(e.getCurrHP() > 0){
				if(e.getResolve() <= 0){
					if(e.getStatus() != "Stun"){
						e.setStatus("Stun");
						e.setAfflicted(2);
						cout << e.getName() << " was Stunned." << endl;
					}
					else{
						cout << e.getName() << " is already Stunned." << endl;
					}
				}
				else{
					e.setResolve(e.getResolve() - 1);
					cout << e.getName() << " lost resolve." << endl;
				}
			}
			break;
		// BEETLE STANCE SKILLS
		// Deflect
		case 10:
			p.curr_stance = "Beetle";
			p.deflecting = true;
			break;
		// ---- ENEMY SKILLS ----------
		// Slam
		case 15:
			if(p.deflecting == true){
				deflectSuccess(1, p);
			}
			if(p.deflecting == false){
				base_damage = 8;
				p.calcHP(base_damage, e.getLuck(), p.resolve);
			}
			break;
		// Sleep
		case 16:
			cout << e.getName() << " dozed..." << endl;
			break;
		// Gnaw
		case 17:
			if(p.deflecting == true){
				deflectSuccess(1, p);
			}
			if(p.deflecting == false){
				base_damage = 10;
				p.calcHP(base_damage, e.getLuck(), p.resolve);
			}
			break;
		// Scrounge
		case 18:
			stat_change = rand()%10 + 1;
			e.setCurrHP(min(e.getMaxHP(), e.getCurrHP() + stat_change));
			cout << e.getName() << " recovered " << stat_change << " HP!" << endl;
			break;
		// Cut
		case 19:
			if(p.deflecting == true){
				deflectSuccess(1, p);
			}
			if(p.deflecting == false){
				base_damage = 12;
				p.calcHP(base_damage, e.getLuck(), p.resolve);
			}
			break;
		// Sharpen
		case 20:
			e.setLuck(e.getLuck() + 1);
			cout << e.getName() << "'s weapon grew sharper!" << endl;
			break;
		// Howl
		case 21:
			if(e.getResolve() < 5){
				cout << e.getName() << "'s resolve increased." << endl;
				e.setResolve(min(5, e.getResolve() + 2));
			}
			else{
				cout << e.getName() << "'s resolve won't go any higher." << endl;
			}
			break;
		// Beastly Barrage
		case 22:
			for(int i = 1; i <= 5; i++){
				sleep(1);
				if(p.deflecting == true){
					deflectSuccess(i, p);
				}
				if(p.deflecting == false){
					base_damage = 2*i;
					p.calcHP(base_damage, e.getLuck(), p.resolve);	
				}
				if(p.curr_HP <= 0){
					break;
				}
			}
			break;
		// THE ZARDLANDER – Zardlander Style: Poison!
		case 23:
			p.status = "Poison";
			p.afflicted = 5;
			cout << "\033[32mPLAYER was Poisoned.\033[0m" << endl;
			break;
		// THE ZARDLANDER – Zardlander Style: Ten-Thousand Strikes!
		case 24:
			for(int i = 1; i <= 3; i++){
				sleep(1);
				if(p.deflecting == true){
					deflectSuccess(i, p);
				}
				if(p.deflecting == false){
					base_damage = 8;
					p.calcHP(base_damage, e.getLuck() + 1, p.resolve);	
				}
				if(p.curr_HP <= 0){
					break;
				}
			}
			sleep(1);
			cout << "The attack didn't exactly live up to its name..." << endl;
			sleep(1);
			break;
		// Oil Slick
		case 25:
			p.status = "Oil";
			cout << "\033[34mPLAYER was covered in Oil.\033[0m" << endl;
			break;
		// Sling
		case 26:
			if(p.deflecting == true){
				deflectSuccess(1, p);
			}
			if(p.deflecting == false){
				base_damage = 12;
				p.calcHP(base_damage, e.getLuck() + 2, p.resolve);
			}
			break;
		// Kobold Trap
		case 27:
			if(p.deflecting == true){
				cout << "But the trap failed!" << endl;
			}
			else{
				stagger(p);
				p.status = "Oil";
				cout << "\033[34mPLAYER was covered in Oil.\033[0m" << endl;
			}
			break;
		// Boulder Heave
		case 28:
			if(p.deflecting == true){
				deflectSuccess(1, p);
			}
			else{
				base_damage = 12;
				p.calcHP(base_damage, e.getLuck(), p.resolve);
				if(rand()%4 == 0 && p.curr_HP > 0){
					stagger(p);
				}
			}
			break;
		// Rock Armor
		case 29:
			if(e.getResolve() < 5){
				cout << e.getName() << "'s resolve increased." << endl;
				e.setResolve(e.getResolve() + 1);
			}
			else{
				cout << e.getName() << "'s resolve won't go any higher." << endl;
			}
			break;
		// Bite
		case 30:
			if(p.deflecting == true){
				deflectSuccess(1, p);
			}
			else{
				base_damage = 15;
				p.calcHP(base_damage, e.getLuck(), p.resolve);
			}
			break;
		// Fireball
		case 31:
			if(p.deflecting == true){
				if(p.status != "Oil"){
					deflectSuccess(1, p);
				}
				else{
					cout << "\033[91mPLAYER is covered in flammable oil! Could not deflect a fire attack!" << endl;
					p.deflecting = false;
					sleep(1);
				}
			}
			if(p.deflecting == false){
				base_damage = 10;
				if(p.status == "Oil"){
					base_damage = 20;
					p.status = "Burn";
					p.afflicted = 5;
					cout << "\033[91mPLAYER was set ablaze!\033[0m" << endl;
				}
				p.calcHP(base_damage, e.getLuck(), p.resolve);
			}
			if(e.getStatus() == "Oil"){
				cout << "\033[91m" << e.getName() << " was set ablaze!\033[0m" << endl;
				e.setStatus("Burn");
				e.setAfflicted(10);
			}
			break;
		// Split Beam
		case 32:
			for(int i = 1; i <= 4; i++){
				sleep(1);
				if(p.deflecting == true){
					deflectSuccess(i, p);
				}
				if(p.deflecting == false){
					base_damage = 6;
					p.calcHP(base_damage, e.getLuck(), p.resolve);	
				}
				if(p.curr_HP <= 0){
					break;
				}
			}
			break;
		// Cosmic Gem
		case 33:
			cout << "A strange power increased the foe's luck." << endl;
			e.setLuck(e.getLuck() + 5);
			break;
		// Ancient Claw
		case 34:
			if(p.deflecting == true){
				deflectSuccess(1, p);
			}
			else{
				base_damage = 20;
				p.calcHP(base_damage, e.getLuck(), p.resolve);
				e.setResolve(min(5, e.getResolve() + 1));
				if(e.getStatus() == "Oil"){
					p.status = "Oil";
					cout << "\033[34mPLAYER was covered in Oil.\033[0m" << endl;
				}
			}
			break;
		// Tar-nado
		case 35:
			if(e.getStatus() == "Burn"){
				cout << "\033[91mThe tar-nado was set ablaze!\033[0m" << endl;
				for(int i = 1; i <= 4; i++){
					sleep(1);
					if(p.deflecting == true){
						if(p.status == "Oil"){
							cout << "\033[91mPLAYER is covered in flammable oil! Could not deflect a fire attack!\033[0m" << endl;
							p.deflecting = false;
							p.status = "Burn";
							p.afflicted = 5;
							cout << "\033[91mPLAYER was set ablaze!\033[0m" << endl;
							sleep(1);
						}
						else{
							deflectSuccess(i, p);
						}
					}
					if(p.deflecting == false){
						base_damage = 6;
						p.calcHP(base_damage, e.getLuck(), p.resolve);	
					}
					if(p.curr_HP <= 0){
						break;
					}
				}
			}
			else{
				for(int i = 1; i <= 8; i++){
					sleep(1);
					if(p.deflecting == true){
						deflectSuccess(i, p);
					}
					if(p.deflecting == false){
						base_damage = rand()%3+1;
						p.calcHP(base_damage, e.getLuck(), p.resolve);	
					}
					if(p.curr_HP <= 0){
						break;
					}
				}
			}
			break;
		// HOT SPRINGS DEITY – Steam Breath
		case 36:
			p.status = "Burn";
			p.afflicted = 5;
			cout << "\033[91mPLAYER was set ablaze!\033[0m" << endl;
			if(p.status == "Oil"){
				p.afflicted = 10;
				p.calcHP(25, e.getLuck(), p.resolve);
			}
			break;
		// HOT SPRINGS DEITY –
		case 37:
		// HOT SPRINGS DEITY –
		case 38:
		// HOT SPRINGS DEITY –
		case 39:
		// FINAL BOSS ATTACK
		case 100:
			p.curr_HP = 1;
			cout << "The attack set PLAYER's health to 1!" << endl;
			break;
		default:
			cout << "But the attack failed." << endl;
			break;
	}
	if(flag == 'e'){
		if(p.curr_stance != p.prev_stance){
			e.setLuck(max(0, e.getLuck() - 2));
		}
		if(p.deflecting == true){
			if(isAttack() != true){
				cout << "There was no attack for PLAYER to deflect!" << endl;
				if(p.resolve > 0){
					cout << "PLAYER lost resolve." << endl;
				}
				p.resolve = max(0, p.resolve - 1);
			}
		}
	}
}