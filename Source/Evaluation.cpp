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

		double weightPadding(edge->weight);
		int incrementableFlowerCount(0);

		STD_VECTOR_CONST_FOREACH_(Flower *, edge->flowers, flowerIt, flowerEnd) {
			const Flower *flower(*flowerIt);

			weightPadding -= flower->power;

			switch (flower->type) {
			case Flower::Type::TREE_EVEN:
				++incrementableFlowerCount;
				break;
			case Flower::Type::TREE_ODD:
				--incrementableFlowerCount;
				break;
			}
		}

		// Test if edge is full and if the epsilon value has an upper bound.
		if ((weightPadding > 0.0) && (incrementableFlowerCount > 0)) {
			double maxEpsilon(weightPadding / static_cast<double>(incrementableFlowerCount));
			if (minEpsilon > maxEpsilon) {
				minEpsilon = maxEpsilon;
				minEdge = edge;
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

		// Only free green flowers are affected.
		if (flower->isFree() && flower->isGreen()) {
			if (minEpsilon > flower->power) {
				minEpsilon = flower->power;
				minGreenFlower = flower;
			}
		}
	}

	return minEpsilon;
}

void applyEpsilon(const double epsilon, const std::vector<Flower *> &flowers)
{
	// INVARIANT: Only the power of tree flowers changes here.

	STD_VECTOR_CONST_FOREACH_(Flower *, flowers, flowerIt, flowerEnd) {
		Flower *flower(*flowerIt);

		// Only free flowers are affected.
		switch (flower->type) {
		case Flower::Type::TREE_EVEN:
			flower->power += epsilon;
			break;
		case Flower::Type::TREE_ODD:
			flower->power -= epsilon;
			break;
		}
	}
}