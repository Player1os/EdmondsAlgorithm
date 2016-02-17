#include "Types.h"

#include "Utility.h"

#include <vector>
#include <iostream>

Flower::Flower()
: type(Type::TREE_EVEN)
, power(0.0)
, parent(nullptr)
, stem(nullptr)
{}

bool Flower::isDumbell() const
{
	return this->type == Type::DUMBELL;
}

bool Flower::isFree() const
{
	return this->type != Type::INTERNAL;
}

bool Flower::isGreen() const
{
	return this->stem != nullptr;
}

const Flower *Flower::root() const
{
	const Flower *currentFlower(this);
	while (currentFlower->parent != nullptr) {
		currentFlower = currentFlower->parent;
	}
	return currentFlower;
}

Edge *Flower::fullEdge(const Flower* flower) const
{
	STD_VECTOR_CONST_FOREACH_(Edge *, this->edges, edgeIt, edgeEnd) {
		Edge *edge(*edgeIt);
		if (edge->isFull()) {
			std::vector<Flower *> &edgeFlowers(edge->flowers);
			if (std::find(edgeFlowers.begin(), edgeFlowers.end(), flower) != edgeFlowers.end()) {
				return edge;
			}
		}
	}
}

Edge *Flower::mEdge() const
{
	STD_VECTOR_CONST_FOREACH_(Edge *, this->edges, edgeIt, edgeEnd) {
		if ((*edgeIt)->type == Edge::Type::M_FULL) {
			return *edgeIt;
		}
	}
}

std::vector<Flower *> Flower::blueSubFlowers() const
{
	std::vector<Flower *> result;

	STD_VECTOR_CONST_FOREACH_(Flower *, this->subFlowers, flowerIt, flowerEnd) {
		Flower *flower(*flowerIt);
		if (flower->isGreen()) {
			std::vector<Flower *> subResult(flower->blueSubFlowers());
			result.insert(result.end(), subResult.begin(), subResult.end());
		} else {
			result.push_back(flower);
		}
	}

	return result;
}

const Flower *Flower::blueStem() const
{
	const Flower *currentStem(this);
	while (currentStem->stem != nullptr) {
		currentStem = currentStem->stem;
	}
	return currentStem;
}

bool Edge::isFull() const
{
	return this->type != Type::REGULAR;
}

Edge::Edge()
: type(Type::REGULAR)
, weight(0.0)
{}

std::vector<Flower *> Edge::freeFlowers() const
{
	std::vector<Flower *> result;

	STD_VECTOR_CONST_FOREACH_(Flower *, this->flowers, flowerIt, flowerEnd) {
		Flower *flower(*flowerIt);
		if (flower->isFree()) {
			result.push_back(flower);
		}
	}

#ifdef ENABLE_ASSERTION
	// ASSERTION: Each edge always connects the correct number of edges.
	if (result.size() != VERTEX_PER_EDGE_COUNT) {
		std::cout << "Assertion failed: An edge was found connecting " << result.size()
			<< " free flowers." << std::endl;
		std::exit(-1);
	}
#endif

	return result;
}