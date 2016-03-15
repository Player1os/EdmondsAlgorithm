#include "Actions.h"
#include "Evaluation.h"
#include "Types.h"
#include "Utility.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

bool testOneIsDumbbell(const std::vector<Flower *> &flowers)
{
	for (int i(0); i < VERTEX_PER_EDGE_COUNT; ++i) {
		if (flowers[i]->isInDumbbell()) {
			return true;
		}
	}
	return false;
}

bool testAllRootEquality(const std::vector<Flower *> &flowers)
{
	const Flower *root(flowers[0]->root());
	for (int i(1); i < VERTEX_PER_EDGE_COUNT; ++i) {
		if (root != flowers[i]->root()) {
			return false;
		}
	}
	return true;
}

int main(const int argc, const char *argv[])
{
	std::cout << std::fixed << std::setprecision(2);

	// Read input.
	int vertexCount(0);
	int edgeCount(0);
	std::cin >> vertexCount;
	std::cin >> edgeCount;
	
	// Initialize Blue Flowers.
	std::vector<Flower *> flowers(vertexCount);
	for (int i(0); i < vertexCount; ++i) {
		Flower *&flower(flowers[i]);
		flower = new Flower();
		flower->vertexId = i + 1;
	}

	// Initialize Edges.
	std::vector<Edge *> edges(edgeCount);
	STD_VECTOR_FOREACH_(Edge *, edges, edgeIt, edgeEnd) {
		*edgeIt = new Edge();
		Edge *edge(*edgeIt);		

		for (int i(0); i < VERTEX_PER_EDGE_COUNT; ++i) {
			int vertexId(0);
			std::cin >> vertexId;

			Flower *blueFlower(flowers[vertexId - 1]);
			blueFlower->edges.push_back(edge);
			edge->flowers.push_back(blueFlower);
			edge->blueFlowers.push_back(blueFlower);
		}
		
		std::cin >> edge->weight;
	}

	// Core algorithm loop.
	int pairingEdgeCount(0);
	FOREVER {
		// Find the min epsilon.
		Edge *minEdge(nullptr);
		double minEdgeEpsilon(findMinEdgeEpsilon(minEdge, edges));
		Flower *minGreenFlower(nullptr);
		double minGreenFlowerEpsilon(findMinGreenFlowerEpsilon(minGreenFlower, flowers));

		// Exit loop if no further power maximization is possible for any flower.
		if ((minEdge == nullptr) && (minGreenFlower == nullptr)) {
			break;
		}

		// Apply the minimum epsilon.
		applyEpsilon(std::min(minEdgeEpsilon, minGreenFlowerEpsilon), flowers);

		// Choose action to be executed.
		if (minEdgeEpsilon > minGreenFlowerEpsilon) {
			executeBurstFlower(minGreenFlower);
			flowers.erase(std::remove(flowers.begin(), flowers.end(), minGreenFlower), flowers.end());
			delete minGreenFlower;

#ifdef ENABLE_DEBUG_CHOSEN_ACTION
			std::cout << "P1|e=" << minGreenFlowerEpsilon << "|"
				<< "G" << minGreenFlower->blueStem()->vertexId << "|";
			std::vector<Flower *> blueSubFlowers(minGreenFlower->blueSubFlowers());
			STD_VECTOR_CONST_FOREACH_(Flower *, blueSubFlowers, subFlowerIt, subFlowerEnd) {
				std::cout << (*subFlowerIt)->vertexId << "|";
			}			
#endif
		} else {
			std::vector<Flower *> freeFlowers(minEdge->freeFlowers());

			if (testOneIsDumbbell(freeFlowers)) {
				executeAppendDumbbell(minEdge, freeFlowers);

#ifdef ENABLE_DEBUG_CHOSEN_ACTION
				std::cout << "P2";
#endif
			} else if (testAllRootEquality(freeFlowers)) {
				flowers.push_back(executeCreateFlower(minEdge, freeFlowers));

#ifdef ENABLE_DEBUG_CHOSEN_ACTION
				std::cout << "P3";
#endif
			} else {
				executeCollapseTree(minEdge, freeFlowers);
				++pairingEdgeCount;

#ifdef ENABLE_DEBUG_CHOSEN_ACTION
				std::cout << "P4";
#endif
			}

#ifdef ENABLE_DEBUG_CHOSEN_ACTION
			std::cout << "|e=" << minEdgeEpsilon << "|"
				<< minEdge->blueFlowers.front()->vertexId << "-"
				<< minEdge->blueFlowers.back()->vertexId;
#endif
		}
#ifdef ENABLE_DEBUG_CHOSEN_ACTION
		std::cout << std::endl;
#endif

#ifdef ENABLE_DEBUG_GRAPH_STATE
		STD_VECTOR_CONST_FOREACH_(Flower *, flowers, flowerIt, flowerEnd) {
			Flower *flower(*flowerIt);
			if (flower->isGreen()) {
				std::cout << "G" << flower->blueStem()->vertexId << "|";
				std::vector<Flower *> blueSubFlowers(flower->blueSubFlowers());
				STD_VECTOR_CONST_FOREACH_(Flower *, blueSubFlowers, subFlowerIt, subFlowerEnd) {
					std::cout << (*subFlowerIt)->vertexId << "|";
				}
			} else {
				std::cout << "B" << flower->vertexId << "|";
				STD_VECTOR_CONST_FOREACH_(Edge *, flower->edges, edgeIt, edgeEnd) {
					const Edge *edge(*edgeIt);
					if (edge->isFull()) {
						for (int i(0); i < VERTEX_PER_EDGE_COUNT; ++i) {
							if (edge->blueFlowers[i] != flower) {
								switch (edge->type)
								{
								case Edge::Type::FULL_IN_PAIRING:
									std::cout << "M";
									break;
								case Edge::Type::FULL_BLOCKING:
									std::cout << "L";
									break;
								}
								std::cout << edge->blueFlowers[i]->vertexId << "|";
								break;
							}
						}
					}					
				}
			}
			std::cout << std::endl;
		}
		std::cout << " --- " << std::endl;
#endif
	}

	// Output Result.
	std::cout << std::setprecision(0);
#ifdef ENABLE_DEBUG_VERBOUS_OUTPUT
	if (pairingEdgeCount < (vertexCount / VERTEX_PER_EDGE_COUNT)) {
		std::cout << "Warning: A complete pairing was not found!" << std::endl;
	}
	std::cout << "The following edges belong to the pairing:" << std::endl;
#endif

	double weightSum(0.0);
	std::reverse(edges.begin(), edges.end());
	STD_VECTOR_FOREACH_(Edge *, edges, edgeIt, edgeEnd) {
		Edge *edge(*edgeIt);
		if (edge->type == Edge::Type::FULL_IN_PAIRING) {
			weightSum += edge->weight;
		}
	}
	std::cout << weightSum << std::endl;

	STD_VECTOR_FOREACH_(Edge *, edges, edgeIt, edgeEnd) {
		Edge *edge(*edgeIt);
		if (edge->type == Edge::Type::FULL_IN_PAIRING) {
			std::cout << edge->blueFlowers[0]->vertexId;
			for (int i(1); i < VERTEX_PER_EDGE_COUNT; ++i) {
				std::cout << " " << edge->blueFlowers[i]->vertexId;
			}
			std::cout << std::endl;
		}
	}

	// Deinitialize all Flowers.
	STD_VECTOR_FOREACH_(Flower *, flowers, flowerIt, flowerEnd) {
		delete *flowerIt;
	}

	// Deinitialize Edges.
	STD_VECTOR_FOREACH_(Edge *, edges, edgeIt, edgeEnd) {
		delete *edgeIt;
	}

	return 0;
}