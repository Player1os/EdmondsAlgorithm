#ifndef EDMONDS_ALGORITHM_TYPES_H
#define EDMONDS_ALGORITHM_TYPES_H

#include "Utility.h"

#include <vector>

class Edge;
class Flower;

class Flower
{
public:
	enum class Type : char
	{
		EVEN_IN_TREE,
		ODD_IN_TREE,
		IN_DUMBBELL,
		INTERNAL
	};

	Type type;
	double power;

	std::vector<Flower *> subFlowers;
	Flower *stemSubFlower;

	Flower *parent;
	std::vector<Flower *> children;

	std::vector<Edge *> edges;

	int vertexId;

	Flower();

	bool isInDumbbell() const;
	bool isFree() const;
	bool isGreen() const;

	Flower *root();
	Edge *inPairingEdge();

	std::vector<Flower *> blueSubFlowers();
	Flower *blueStem();
};

class Edge
{
public:
	enum class Type : char
	{
		REGULAR,
		FULL_IN_PAIRING,
		FULL_BLOCKING
	};

	Edge();

	Type type;
	double weight;

	std::vector<Flower *> flowers;
	std::vector<Flower *> blueFlowers;

	bool isFull() const;

	std::vector<Flower *> freeFlowers();
};

#endif // EDMONDS_ALGORITHM_TYPES_H