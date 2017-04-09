#pragma once
#include <vector>
#include <iostream>
#include "Item.h"

const int carryCapacity = 30;

class Solution
{
public:
	Solution(std::vector<Item*>* items, bool random);
	Solution(Solution* solution);
	~Solution();
	void calculateWeight();
	void calculateValue();
	int getWeight() { return weight; }
	int getValue() { return value; }
	void Mutuj();
	int getFitness();
	int getLength();
	std::vector<bool> solution;
	std::vector<Item*>* items;

private:
	int weight;
	int value;
	int fitness;
	std::vector<bool> generateRandom();
};

