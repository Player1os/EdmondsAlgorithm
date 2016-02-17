#ifndef ACTIONS_H
#define ACTIONS_H

#include "Types.h"

#include <vector>

// Implementation of (P1).
void executeBurstFlower(const Flower *greenFlower);

// Implementation of (P2).
void executeAppendDumbell(Edge *minEdge, std::vector<Flower *> &freeFlowers);

// Implementation of (P3).
Flower *executeCreateFlower(Edge *minEdge, std::vector<Flower *> &freeFlowers);

// Implementation of (P4).
void executeCollapseTree(Edge *minEdge, std::vector<Flower *> &freeFlowers);

#endif // ACTIONS_H