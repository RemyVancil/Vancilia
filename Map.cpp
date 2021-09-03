#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include "Map.h"
using namespace std;

Map::Map(){

}

int Map::getID(){
	return ID;
}

int Map::getBiome(){
	return biome;
}

int Map::getLeft(){
	return left;
}

int Map::getRight(){
	return right;
}

int Map::getBack(){
	return back;
}

void Map::setID(int new_ID){
	ID = new_ID;
}

void Map::setBiome(int new_biome){
	biome = new_biome;
}

void Map::setLeft(int new_left){
	left = new_left;
}

void Map::setRight(int new_right){
	right = new_right;
}

void Map::setBack(int new_back){
	back = new_back;
}