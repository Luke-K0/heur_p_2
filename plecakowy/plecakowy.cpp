// plecakowy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include "Item.h"
#include "Solution.h"

const int itemCount = 30;
const int maxValue = 10;
const int maxWeight = 10;
const int populationSize = 200;

bool compareSolutions(Solution* a, Solution* b);

int main()
{
	std::vector<Item*> items(itemCount);
	for (unsigned int i = 0; i < itemCount; i++)
	{
		int value = rand() % maxValue + 1;
		int weight = rand() % maxWeight + 1;
		items[i] = new Item(weight, value);
	}
	
	std::srand(std::time(0));
	std::vector<Solution*> currentGeneration(populationSize);
	for (int i = 0; i < populationSize; i++)
	{
		currentGeneration[i] = new Solution(&items, true);
	}
	
	std::sort(currentGeneration.begin(), currentGeneration.end(), compareSolutions);
	
	//auto weightValue = getTotalWeightValue(&items, solution);
	//std::cout << "Weight: " << weightValue.first << " Value: " << weightValue.second << "\n";
	std::cout << "press any key";
	getchar();
    return 0;
}

bool compareSolutions(Solution* a, Solution* b)
{
	return a->getValue() > b->getValue();
}

std::pair<int, int> getTotalWeightValue(std::vector<Item*>* items, std::vector<bool>* solution)
{
	int totalWeight = 0;
	int totalValue = 0;

	for (unsigned int i = 0; i < items->size(); i++)
	{
		if ((*solution)[i])
		{
			auto item = (*items)[i];
			totalWeight += item->weight;
			totalValue += item->value;
		}
	}

	return std::pair<int, int>(totalWeight, totalValue);
}

