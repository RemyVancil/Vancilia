#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
using namespace std;

#ifndef ENEMY_H
#define ENEMY_H

// Enemy data
class Enemy
{
	private:
		int ID;
		string name;
		int max_HP;
		int curr_HP;
		int resolve;
		int luck;
		//vector<Item> drops;
		string status;
		vector<int> skills;
		int afflicted;
	public:
		// Constructor
		Enemy();
		// Getters
		int getID();
		string getName();
		int getMaxHP();
		int getCurrHP();
		int getResolve();
		int getLuck();
		string getStatus();
		vector<int> getSkills();
		int getAfflicted();
		// Setters
		void setID(int);
		void setName(string);
		void setMaxHP(int);
		void setCurrHP(int);
		void setResolve(int);
		void setLuck(int);
		void setStatus(string);
		void setSkills(vector<int>);
		void setAfflicted(int);
		// Combat functions
		void calcHP(int, int, int);
		int AI_action(int, string);
};

#endif