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

const int itemCount = 50;
const int maxValue = 9;
const int maxWeight = 9;
const int populationSize = 100;
const int maxGenerations = 300;
const double mutationRate = 0.1;

bool compareSolutions(Solution* a, Solution* b);
std::vector<std::pair<Solution*, Solution*>> GenerujReproduktorow(std::vector<Solution*>* generacja);
std::pair<Solution*, Solution*> CrossOver(std::pair<Solution*, Solution*> rodzice);
Solution* LosujReproduktora(std::vector<Solution*>* generacja);
void RysujMnieTuSolucje(Solution* solution);

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
	auto currentGeneration = new std::vector<Solution*>(populationSize);
	for (int i = 0; i < populationSize; i++)
	{
		(*currentGeneration)[i] = new Solution(&items, true);
	}
	
	int numerPokolenia = 0;
	Solution* bestSolution = NULL;

	while (numerPokolenia < maxGenerations)
	{
		std::sort((*currentGeneration).begin(), (*currentGeneration).end(), compareSolutions);
		if (bestSolution == NULL)
		{
			bestSolution = (*currentGeneration)[0];
		}

		std::cout << "Pokolenie: " << numerPokolenia << "\twaga: " << (*currentGeneration)[0]->getWeight() << " wartosc: " << (*currentGeneration)[0]->getValue() << " best waga: " << bestSolution->getWeight() << " best wartosc: " << bestSolution->getValue() << "\n";
		//RysujMnieTuSolucje((*currentGeneration)[0]);

		auto newGeneration = new std::vector<Solution*>();
		std::vector<std::pair<Solution*, Solution*>> reproduktorzy = GenerujReproduktorow(currentGeneration);
		for each (auto para in reproduktorzy)
		{
			std::pair<Solution*, Solution*> potomkowie = CrossOver(para);
			if (((double)rand() / (RAND_MAX)) < mutationRate)
			{
				potomkowie.first->Mutuj();
			}
			if (((double)rand() / (RAND_MAX)) < mutationRate)
			{
				potomkowie.second->Mutuj();
			}

			(*newGeneration).push_back(potomkowie.first);
			(*newGeneration).push_back(potomkowie.second);
		}

		for each (auto solution in (*newGeneration))
		{
			if (solution->getFitness() > bestSolution->getFitness())
			{
				bestSolution = solution;
			}
		}
		
		for each (auto solution in (*currentGeneration))
		{
			if (solution != bestSolution)
			{
				delete solution;
			}
		}
		delete currentGeneration;
		
		currentGeneration = newGeneration;
		numerPokolenia++;
	}
	
	std::cout << "\nBest solution - waga: " << bestSolution->getWeight() << " wartosc: " << bestSolution->getValue() << "\n";
	RysujMnieTuSolucje(bestSolution);
	getchar();
    return 0;
}

bool compareSolutions(Solution* a, Solution* b)
{
	return a->getFitness() > b->getFitness();
}

std::vector<std::pair<Solution*, Solution*>> GenerujReproduktorow(std::vector<Solution*>* generacja)
{
	int targetCount = generacja->size() / 2;
	std::vector<std::pair<Solution*, Solution*>> result;
	while (result.size() < targetCount)
	{
		result.push_back(std::pair<Solution*, Solution*>(LosujReproduktora(generacja), LosujReproduktora(generacja)));
	}

	return result;
}

std::pair<Solution*, Solution*> CrossOver(std::pair<Solution*, Solution*> rodzice)
{
	Solution* child1 = new Solution(rodzice.first);
	Solution* child2 = new Solution(rodzice.second);

	for (int i = 0; i < child1->getLength(); i++)
	{
		if (i < child1->getLength() / 2)
		{
			child1->solution[i] = rodzice.first->solution[i];
			child2->solution[i] = rodzice.second->solution[i];
		}
		else
		{
			child1->solution[i] = rodzice.second->solution[i];
			child2->solution[i] = rodzice.first->solution[i];
		}
	}

	child1->calculateValue();
	child1->calculateWeight();
	child2->calculateValue();
	child2->calculateWeight();

	return std::pair<Solution*, Solution*>(child1, child2);
}

Solution* LosujReproduktora(std::vector<Solution*>* generacja)
{
	int  sumOfAllFitness = 0;
	for each (auto solution in (*generacja))
	{
		sumOfAllFitness += solution->getFitness();
	}

	std::vector<double> progi(generacja->size());
	double offset = 0;

	for (int i = 0; i < generacja->size(); i++)
	{
		double procent = ((*generacja)[i]->getFitness()) / (double)sumOfAllFitness;
		progi[i] = offset;
		offset += procent;
	}

	int index = progi.size() - 1;
	double random = ((double)rand() / (RAND_MAX));
	for (int i = 0; i < progi.size() - 1; i++)
	{
		if (progi[i] <= random && progi[i + 1] >= random)
		{
			index = i;
			break;
		}
	}

	return (*generacja)[index];
}

void RysujMnieTuSolucje(Solution * solution)
{
	std::cout << "[";
	for each (auto item in *(solution->items))
	{
		std::cout << "|" << item->weight << "," << item->value << "|";
	}
	std::cout << "]\n";

	std::cout << "[";
	for each (bool item in (solution->solution))
	{
		if (item)
		{
			std::cout << "| X |";
		}
		else
		{
			std::cout << "|   |";
		}
	}
	std::cout << "]\n\n";
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

