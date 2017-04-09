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


const int carryCapacity = 50;
const int itemCount = 30;
const int maxValue = 10;
const int maxWeight = 10;
const int populationSize = 200;

std::vector<bool>* generateRandom(std::vector<Item*>* items);
std::pair<int, int> getTotalWeightValue(std::vector<Item*>* items, std::vector<bool>* solution);

int main()
{
	std::srand(std::time(0));
	std::vector<Item*> items(itemCount);
	for (unsigned int i = 0; i < itemCount; i++)
	{
		int value = rand() % maxValue + 1;
		int weight = rand() % maxWeight + 1;
		items[i] = new Item(weight, value);
	}
		
	std::vector<std::vector<bool>*> currentGeneration(populationSize);
	for (int i = 0; i < populationSize; i++)
	{
		currentGeneration[i] = generateRandom(&items);
	}
	
	std::sort(currentGeneration.begin(), currentGeneration.end());
	
	//auto weightValue = getTotalWeightValue(&items, solution);
	//std::cout << "Weight: " << weightValue.first << " Value: " << weightValue.second << "\n";
	getchar();
    return 0;
}

std::vector<bool>* generateRandom(std::vector<Item*>* items)
{
	std::vector<bool>* solution = new std::vector<bool>(items->size());
	bool stop = false;

	while (!stop)
	{
		int index = rand() % (int)items->size();
		(*solution)[index] = true;

		int totalWeight = getTotalWeightValue(items, solution).first;
		if (totalWeight > carryCapacity)
		{
			(*solution)[index] = false;
			stop = true;
		}
	}

	return solution;
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

