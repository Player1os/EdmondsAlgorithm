#include "Actions.h"
#include "Evaluation.h"
#include "Types.h"
#include "Utility.h"

#include <algorithm>
#include <iostream>
#include <vector>

// SUGGSETIONS
// There may be a problem with double weights, investigate if it becomes an issue.

// A good idea would be to see if it is possible to get a valid epsilon.
// If all vertices are blocked we may wish to stop the process.

// So the result of the algorithm is a complete min-1-factor if |M|=n/2,
// or a partial min-1-factor otherwise.

// TODO: needs to include cases for odd number of vectors.
// TODO: needs to account for the fact that it is not always possible.

bool testAllIsDumbell(const std::vector<Flower *> &flowers)
{
	bool result(flowers[0]->isDumbell());
	for (int i(1); i < VERTEX_PER_EDGE_COUNT; ++i) {
		result = result && flowers[i]->isDumbell();
	}
	return result;
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
	// Read input.
	int vertexCount(0);
	int edgeCount(0);
	std::cin >> vertexCount;
	std::cin >> edgeCount;
	
	// Initialize Blue Flowers.
	std::vector<Flower *> flowers(vertexCount);
	STD_VECTOR_FOREACH_(Flower *, flowers, flowerIt, flowerEnd) {
		*flowerIt = new Flower();
	}

	// Initialize Edges.
	std::vector<Edge *> edges(edgeCount);
	STD_VECTOR_FOREACH_(Edge *, edges, edgeIt, edgeEnd) {
		*edgeIt = new Edge();
		Edge *edge(*edgeIt);		

		for (int i = 0; i < VERTEX_PER_EDGE_COUNT; ++i) {
			int vertexId(-1);
			std::cin >> vertexId;

			Flower *blueFlower(flowers[vertexId]);
			blueFlower->edges.push_back(edge);
			edge->flowers.push_back(blueFlower);
			edge->blueFlowers.push_back(blueFlower);

			edge->vertexIds.push_back(vertexId);
		}
		
		std::cin >> edge->weight;
	}

	// Core algorithm loop.
	int mEdgeCount(0);
	while (mEdgeCount < (vertexCount / VERTEX_PER_EDGE_COUNT)) {
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
		} else {
			std::vector<Flower *> freeFlowers(minEdge->freeFlowers());

			if (testAllIsDumbell(freeFlowers)) {
				executeAppendDumbell(minEdge, freeFlowers);
			} else if (testAllRootEquality(freeFlowers)) {
				flowers.push_back(executeCreateFlower(minEdge, freeFlowers));
			} else {
				executeCollapseTree(minEdge, freeFlowers);
				++mEdgeCount;
			}			
		}		
	}

	// Deinitialize all Flowers.
	STD_VECTOR_CONST_FOREACH_(Flower *, flowers, flowerIt, flowerEnd) {
		delete *flowerIt;
	}

	// Deinitialize Edges.
	STD_VECTOR_CONST_FOREACH_(Edge *, edges, edgeIt, edgeEnd) {
		delete *edgeIt;
	}

	// Output Result.
	if (mEdgeCount < (vertexCount / VERTEX_PER_EDGE_COUNT)) {
		std::cout << "Warning: A complete pairing was not found!" << std::endl;
	}
	std::cout << "The following edges belong to the pairing:" << std::endl;

	double weightSum(0.0);	
	STD_VECTOR_CONST_FOREACH_(Edge *, edges, edgeIt, edgeEnd) {
		Edge *edge(*edgeIt);

		if (edge->type == Edge::Type::M_FULL) {
			weightSum += edge->weight;
			std::cout << " " << edge->vertexIds[0];
			for (int i(1); i < VERTEX_PER_EDGE_COUNT; ++i) {
				std::cout << " - " << edge->vertexIds[i];
			}
			std::cout << std::endl;
		}		
	}
	std::cout << "Their total weight sum is: " << weightSum << std::endl;

	return 0;
}