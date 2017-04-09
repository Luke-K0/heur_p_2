#include "stdafx.h"
#include "Solution.h"

Solution::Solution(std::vector<Item*>* items, bool random)
{
	this->items = items;
	if (random)
	{
		this->solution = generateRandom();
	}
	else
	{
		this->solution = std::vector<bool>(items->size());
	}

	calculateValue();
	calculateWeight();
}

Solution::Solution(Solution* solution)
{
	this->items = solution->items;
	this->solution = std::vector<bool>(items->size());
	
	calculateValue();
	calculateWeight();
}

Solution::~Solution()
{
}

std::vector<bool> Solution::generateRandom()
{
	Solution newSolution(this->items, false);
	bool stop = false;

	while (!stop)
	{
		int index = rand() % (int)items->size();
		newSolution.solution[index] = true;
		newSolution.calculateWeight();

		if (newSolution.getWeight() > carryCapacity)
		{
			newSolution.solution[index] = false;
			newSolution.calculateWeight();
			stop = true;
		}
	}

	return newSolution.solution;
}

void Solution::calculateWeight()
{
	int totalWeight = 0;

	for (unsigned int i = 0; i < items->size(); i++)
	{
		if (solution[i])
		{
			auto item = (*items)[i];
			totalWeight += item->weight;
		}
	}

	weight = totalWeight;
	fitness = weight > carryCapacity ? 0 : value;
}

void Solution::calculateValue()
{
	int totalValue = 0;

	for (unsigned int i = 0; i < items->size(); i++)
	{
		if (solution[i])
		{
			auto item = (*items)[i];
			totalValue += item->value;
		}
	}

	value = totalValue;
	fitness = weight > carryCapacity ? 0 : value;
}

void Solution::Mutuj()
{
	//std::cout << "Mutuje!" << std::endl;

	std::vector<int> trueIndexes;
	std::vector<int> falseIndexes;

	for (int i = 0; i < items->size(); i++)
	{
		solution[i] ? trueIndexes.push_back(i) : falseIndexes.push_back(i);
	}

	int trueIndex = rand() % trueIndexes.size();
	int falseIndex = rand() % falseIndexes.size();

	solution[trueIndex] = false;
	solution[falseIndex] = true;

	calculateValue();
	calculateWeight();
}

int Solution::getFitness()
{
	return fitness;
}

int Solution::getLength()
{
	return solution.size();
}