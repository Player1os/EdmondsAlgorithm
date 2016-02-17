#ifndef TYPES_H
#define TYPES_H

#include "Utility.h"

#include <vector>

class Flower
{
public:
	enum class Type : char
	{
		TREE_EVEN,
		TREE_ODD,
		DUMBELL,
		INTERNAL
	};

	Type type;
	double power;

	std::vector<Flower *> subFlowers;
	Flower *stem;

	Flower *parent;
	std::vector<Flower *> children;

	std::vector<Edge *> edges;

	Flower();

	bool isDumbell() const;
	bool isFree() const;
	bool isGreen() const;

	const Flower *root() const;

	Edge *fullEdge(const Flower* flower) const;
	Edge *mEdge() const;

	std::vector<Flower *> blueSubFlowers() const;
	const Flower *blueStem() const;
};

class Edge
{
public:
	enum class Type : char
	{
		REGULAR,
		M_FULL,
		L_FULL
	};

	Edge();

	Type type;
	double weight;

	std::vector<Flower *> flowers;
	std::vector<Flower *> blueFlowers;

	std::vector<int> vertexIds;

	bool isFull() const;

	std::vector<Flower *> freeFlowers() const;
};

#endif // TYPES_H