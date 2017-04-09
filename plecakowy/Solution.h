#pragma once
#include <vector>
#include "Item.h"

const int carryCapacity = 50;

class Solution
{
public:
	Solution(std::vector<Item*>* items, bool random);
	Solution(std::vector<Item*>* items, std::vector<bool> solution);
	~Solution();
	void calculateWeight();
	void calculateValue();
	int getWeight() { return weight; }
	int getValue() { return value; }

private:
	int weight;
	int value;
	std::vector<Item*>* items;
	std::vector<bool> solution;	
	std::vector<bool> generateRandom();
};

