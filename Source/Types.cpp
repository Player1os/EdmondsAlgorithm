#include "Types.h"

#include "Utility.h"

#include <vector>
#include <iostream>

Flower::Flower()
: type(Type::EVEN_IN_TREE)
, power(0.0)
, parent(nullptr)
, stemSubFlower(nullptr)
, vertexId(0)
{}

bool Flower::isInDumbbell() const
{
	return this->type == Type::IN_DUMBBELL;
}

bool Flower::isFree() const
{
	return this->type != Type::INTERNAL;
}

bool Flower::isGreen() const
{
	return this->stemSubFlower != nullptr;
}

Flower *Flower::root()
{
	Flower *currentFlower(this);
	while (currentFlower->parent != nullptr) {
		currentFlower = currentFlower->parent;
	}
	return currentFlower;
}

Edge *Flower::inPairingEdge()
{
	STD_VECTOR_FOREACH_(Edge *, this->edges, edgeIt, edgeEnd) {
		Edge *edge(*edgeIt);
		if (edge->type == Edge::Type::FULL_IN_PAIRING) {
			return edge;
		}
	}
#ifdef ENABLE_DEBUG
	// ASSERTION: This method should not be called in a case where the desired edge does not exist.
	std::cout << "Assertion failed: inPairingEdge method called when no such edge exists." << std::endl;
	std::exit(-1);
#endif
	return nullptr;
}

std::vector<Flower *> Flower::blueSubFlowers()
{
	std::vector<Flower *> result;
	STD_VECTOR_FOREACH_(Flower *, this->subFlowers, flowerIt, flowerEnd) {
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

Flower *Flower::blueStem()
{
	Flower *currentStem(this);
	while (currentStem->stemSubFlower != nullptr) {
		currentStem = currentStem->stemSubFlower;
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

std::vector<Flower *> Edge::freeFlowers()
{
	std::vector<Flower *> result;

	STD_VECTOR_FOREACH_(Flower *, this->flowers, flowerIt, flowerEnd) {
		Flower *flower(*flowerIt);
		if (flower->isFree()) {
			result.push_back(flower);
		}
	}

#ifdef ENABLE_DEBUG
	// ASSERTION: Each edge always connects the correct number of edges.
	if (result.size() != VERTEX_PER_EDGE_COUNT) {
		std::cout << "Assertion failed: An edge was found connecting " << result.size()
			<< " free flowers." << std::endl;
		std::exit(-1);
	}
#endif

	return result;
}