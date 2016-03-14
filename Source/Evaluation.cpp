#include "Evaluation.h"

#include "Types.h"
#include "Utility.h"

#include <vector>
#include <limits>

double findMinEdgeEpsilon(Edge *&minEdge, const std::vector<Edge *> &edges)
{
	// INVARIANT: No change to the graph state occurs here.

	double minEpsilon(std::numeric_limits<double>::max());

	STD_VECTOR_CONST_FOREACH_(Edge *, edges, edgeIt, edgeEnd) {
		Edge *edge(*edgeIt);

		if (!edge->isFull()) {
			double weightPadding(edge->weight);
			int incrementableFlowerCount(0);

			STD_VECTOR_CONST_FOREACH_(Flower *, edge->flowers, flowerIt, flowerEnd) {
				const Flower *flower(*flowerIt);

				weightPadding -= flower->power;

				switch (flower->type) {
				case Flower::Type::EVEN_IN_TREE:
					++incrementableFlowerCount;
					break;
				case Flower::Type::ODD_IN_TREE:
					--incrementableFlowerCount;
					break;
				}
			}

			// Test if edge is full and if the epsilon value has an upper bound.
			double maxEpsilon(weightPadding);
			if (incrementableFlowerCount > 0) {
				maxEpsilon /= static_cast<double>(incrementableFlowerCount);
				if (minEpsilon > maxEpsilon) {
					minEpsilon = maxEpsilon;
					minEdge = edge;
				}
			}
		}
	}

	return minEpsilon;
}

double findMinGreenFlowerEpsilon(Flower *&minGreenFlower, const std::vector<Flower *> &flowers)
{
	// INVARIANT: No change to the graph state occurs here.

	double minEpsilon(std::numeric_limits<double>::max());

	STD_VECTOR_CONST_FOREACH_(Flower *, flowers, flowerIt, flowerEnd) {
		Flower *flower(*flowerIt);

		// Only tree odd green flowers are affected.
		if ((flower->type == Flower::Type::ODD_IN_TREE) && flower->isGreen()) {
			if (minEpsilon > flower->power) {
				minEpsilon = flower->power;
				minGreenFlower = flower;
			}
		}
	}

	return minEpsilon;
}

void applyEpsilon(double epsilon, const std::vector<Flower *> &flowers)
{
	// INVARIANT: Only the power of tree flowers changes here.

	STD_VECTOR_CONST_FOREACH_(Flower *, flowers, flowerIt, flowerEnd) {
		Flower *flower(*flowerIt);

		// Only tree flowers are affected.
		switch (flower->type) {
		case Flower::Type::EVEN_IN_TREE:
			flower->power += epsilon;
			break;
		case Flower::Type::ODD_IN_TREE:
			flower->power -= epsilon;
			break;
		}
	}
}