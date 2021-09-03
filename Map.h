#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
using namespace std;

#ifndef MAP_H
#define MAP_H

// directed graph
class Map
{
	private:
		int ID;
		int biome;
		int left;
		int right;
		int back;
	public:
		Map();
		int getID();
		int getBiome();
		int getLeft();
		int getRight();
		int getBack();
		void setID(int);
		void setBiome(int);
		void setLeft(int);
		void setRight(int);
		void setBack(int);
};

#endif

/*
generate map func

FOREST
0. Nothing
1. Rat (35%) / Slime (30%) /  Bandit (20%) / Random (15%)
2. Rat (35%) / Slime (30%) /  Bandit (20%) / Random (15%)
3. Rat (35%) / Slime (30%) /  Bandit (20%) / Random (15%)
4. Rat (35%) / Slime (30%) /  Bandit (20%) / Random (15%)
5. Wolf Demon (100%) – guaranteed to drop Ring, and can get 5 bullets from NPC in next town
6. BOSS: The Zardlander (100%)


Move to node
Call void event(biome, num_enemy) which uses biome to look up encounter odds and execute
Within event():
	If num_enemy > 3:
		call random_event() func
		return
	Else:
		Generate random num 1-100
		If 0 < rand <= 85:
			int enemy_ID = biome.get_enemy(rand)
			combat_event(enemy_ID) func
			return
		Else If 85 < rand <= 100:
			call random_event() func
			return
*/