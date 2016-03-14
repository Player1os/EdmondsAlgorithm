#ifndef EDMONDS_ALGORITHM_EVALUATION_H
#define EDMONDS_ALGORITHM_EVALUATION_H

#include "Types.h"

#include <vector>

// Checks for violations of (I1)
double findMinEdgeEpsilon(Edge *&minEdge, const std::vector<Edge *> &edges);

// Checks for violations of (I2)
double findMinGreenFlowerEpsilon(Flower *&minGreenFlower, const std::vector<Flower *> &flowers);

// Apply power changes to flowers using the selected epsilon value.
void applyEpsilon(double epsilon, const std::vector<Flower *> &flowers);

#endif // EDMONDS_ALGORITHM_EVALUATION_H