#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include "Enemy.h"
#include "Player.h"
using namespace std;


#ifndef SKILL_H
#define SKILL_H

// Player data
class Skill
{
	private:
		int ID;
		string name;
		bool attack;
	public:
		Skill();
		int getID();
		string getName();
		bool isAttack();
		void setID(int);
		void setName(string);
		void setAttack(bool);
		void stagger(Player&);
		void deflectSuccess(int, Player&);
		void skillEffect(Player&, Enemy&, char);
};

#endif