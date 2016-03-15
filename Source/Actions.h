#ifndef EDMONDS_ALGORITHM_ACTIONS_H
#define EDMONDS_ALGORITHM_ACTIONS_H

#include "Types.h"

#include <vector>

// Implementation of (P1).
void executeBurstFlower(Flower *greenFlower);

// Implementation of (P2).
void executeAppendDumbbell(Edge *minEdge, std::vector<Flower *> &freeFlowers);

// Implementation of (P3).
Flower *executeCreateFlower(Edge *minEdge, std::vector<Flower *> &freeFlowers);

// Implementation of (P4).
void executeCollapseTree(Edge *minEdge, std::vector<Flower *> &freeFlowers);

#endif // EDMONDS_ALGORITHM_ACTIONS_H