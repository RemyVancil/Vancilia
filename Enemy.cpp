#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <time.h>
#include <vector>
#include "Enemy.h"
using namespace std;

Enemy::Enemy(){

}

int Enemy::getID(){
	return ID;
}

string Enemy::getName(){
	return name;
}

int Enemy::getMaxHP(){
	return max_HP;
}

int Enemy::getCurrHP(){
	return curr_HP;
}

int Enemy::getResolve(){
	return resolve;
}

int Enemy::getLuck(){
	return luck;
}

string Enemy::getStatus(){
	return status;
}

vector<int> Enemy::getSkills(){
	return skills;
}

int Enemy::getAfflicted(){
	return afflicted;
}

void Enemy::setID(int new_ID){
	ID = new_ID;
}

void Enemy::setName(string new_name){
	name = new_name;
}

void Enemy::setMaxHP(int new_max_HP){
	max_HP = new_max_HP;
}

void Enemy::setCurrHP(int new_curr_HP){
	curr_HP = new_curr_HP;
}

void Enemy::setResolve(int new_resolve){
	resolve = new_resolve;
}

void Enemy::setLuck(int new_luck){
	luck = new_luck;
}

void Enemy::setStatus(string new_status){
	status = new_status;
}

void Enemy::setSkills(vector<int> new_skills){
	skills = new_skills;
}

void Enemy::setAfflicted(int new_afflicted){
	afflicted =  new_afflicted;
}

void Enemy::calcHP(int base_damage, int p_luck, int e_res){
	int damage, crit = round(p_luck * 5 + 10);
	if(crit > (rand()%100+1)){
		cout << "A critical hit!" << endl;
		damage = round(1.3 * base_damage);
	}
	else{
		damage = round((pow(base_damage, 2)) / (base_damage + e_res));
	}
	if(damage <= 0){
		damage = 1;
	}
	curr_HP = max(0, curr_HP - damage);
	cout << name << " took " << damage << " damage!" << endl;
}

int Enemy::AI_action(int p_HP, string p_status){
	int out = 0;
	switch(getID()){
		// Wolf Demon AI
		case 3:
			if(getResolve() < 2){
				out = skills[1];	
			}
			else{
				if(rand() % 2 == 0){
					out = skills[0];
				}
				else{
					out = skills[2];
				}
			}
			break;
		// The Zardlander AI
		case 4:
			if(p_status == "NONE"){
				out = skills[2];
			}
			else{
				int r = rand() % 6;
				if(r <= 2){
					out = skills[0];
				}
				else{
					if(p_HP > 50){
						if(r == 3){
							out = skills[1];
						}
						else{
							out = skills[3];
						}
					}
					else{
						if(r == 3){
							out = skills[3];
						}
						else{
							out = skills[1];
						}			
					}
				}
			}
			break;
		// Hot Springs Deity AI
		case 11:
			if(p_status == "NONE" || p_status == "Oil"){
				out = skills[0];
			}
		// Generic enemy AI
		default:
			out = skills[rand() % skills.size()];
			break;
	}
	return out;
}