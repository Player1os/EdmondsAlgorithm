#include "Actions.h"

#include "Types.h"
#include "Utility.h"

#include <algorithm>
#include <vector>

#if VERTEX_PER_EDGE_COUNT != 2
CREATE A COMPILATION ERROR
#endif

// Properly sorts the flowers:
// The first flower becomes the start flower, then follows an odd number of flowers,
// then follows the end flower, then follows an even number of flowers.
void reorderFlowers(std::vector<Flower *> &flowers, int &startFlowerId, int &endFlowerId)
{
	int flowersCount(static_cast<int>(flowers.size()));

	// Determine the size of the segment of subflowers that would remain in the tree.
	int segmentSize(endFlowerId - startFlowerId + 1);
	if (segmentSize < 1) {
		segmentSize += flowersCount;
	}

	// If the segment size is even then the segment's complement contains the disired subflowers.
	if ((segmentSize % 2) == 0) {
		std::reverse(flowers.begin(), flowers.end());
		startFlowerId = flowersCount - (startFlowerId + 1);
		endFlowerId = flowersCount - (endFlowerId + 1);
	}

	// If needed the subflower array will be cyclically shifted to begin with the start subflower.
	if (startFlowerId > 0) {
		std::vector<Flower *> currentSubFlowers(flowers);
		for (int i(0); i < flowersCount; ++i) {
			flowers[i] = currentSubFlowers[(startFlowerId + i) % flowersCount];
		}
	}

	// Determine new start and end indices.
	if (startFlowerId > endFlowerId) {
		endFlowerId += flowersCount - startFlowerId;
	} else {
		endFlowerId -= startFlowerId;
	}	
	startFlowerId = 0;
}

std::vector<Flower *> v3() {
	std::vector<Flower *> v;	
	v.push_back(new Flower());
	v.back()->vertexId = 1;
	v.push_back(new Flower());
	v.back()->vertexId = 2;
	v.push_back(new Flower());
	v.back()->vertexId = 3;
	return v;
}

std::vector<Flower *> v5() {
	std::vector<Flower *> v(v3());
	v.push_back(new Flower());
	v.back()->vertexId = 4;
	v.push_back(new Flower());
	v.back()->vertexId = 5;
	return v;
}

bool eq(std::vector<Flower *> &a, std::vector<int> &b) {
	if (a.size() != b.size()) {
		return false;
	}
	for (std::vector<Flower *>::size_type i(0); i < a.size(); ++i) {
		if (a[i]->vertexId != b[i]) {
			return false;
		}
	}
	return true;
}

void test() {
	int s, e;

	std::vector<Flower *> a1(v3());
	std::vector<int> r1({ 1, 2, 3 });
	s = 0; e = 0;
	reorderFlowers(a1, s, e);
	if (!(eq(a1, r1) && (s == 0) && (e == 0))) {
		exit(-1);
	}

	std::vector<Flower *> a2(v3());
	std::vector<int> r2({ 2, 3, 1 });
	s = 1; e = 1;
	reorderFlowers(a2, s, e);
	if (!(eq(a2, r2) && (s == 0) && (e == 0))) {
		exit(-1);
	}

	std::vector<Flower *> a3(v3());
	std::vector<int> r3({ 3, 1, 2 });
	s = 2; e = 2;
	reorderFlowers(a3, s, e);
	if (!(eq(a3, r3) && (s == 0) && (e == 0))) {
		exit(-1);
	}

	std::vector<Flower *> a4(v3());
	std::vector<int> r4({ 1, 3, 2 });
	s = 0; e = 1;
	reorderFlowers(a4, s, e);
	if (!(eq(a4, r4) && (s == 0) && (e == 2))) {
		exit(-1);
	}

	std::vector<Flower *> a5(v3());
	std::vector<int> r5({ 2, 3, 1 });
	s = 1; e = 0;
	reorderFlowers(a5, s, e);
	if (!(eq(a5, r5) && (s == 0) && (e == 2))) {
		exit(-1);
	}

	std::vector<Flower *> a6(v3());
	std::vector<int> r6({ 1, 2, 3 });
	s = 0; e = 2;
	reorderFlowers(a6, s, e);
	if (!(eq(a6, r6) && (s == 0) && (e == 2))) {
		exit(-1);
	}

	std::vector<Flower *> a7(v3());
	std::vector<int> r7({ 3, 2, 1 });
	s = 2; e = 0;
	reorderFlowers(a7, s, e);
	if (!(eq(a7, r7) && (s == 0) && (e == 2))) {
		exit(-1);
	}

	std::vector<Flower *> a8(v5());
	std::vector<int> r8({ 2, 1, 5, 4, 3 });
	s = 1; e = 4;
	reorderFlowers(a8, s, e);
	if (!(eq(a8, r8) && (s == 0) && (e == 2))) {
		exit(-1);
	}

	std::vector<Flower *> a9(v5());
	std::vector<int> r9({ 5, 1, 2, 3, 4 });
	s = 4; e = 1;
	reorderFlowers(a9, s, e);
	if (!(eq(a9, r9) && (s == 0) && (e == 2))) {
		exit(-1);
	}

	std::vector<Flower *> a10(v5());
	std::vector<int> r10({ 5, 4, 3, 2, 1 });
	s = 4; e = 0;
	reorderFlowers(a10, s, e);
	if (!(eq(a10, r10) && (s == 0) && (e == 4))) {
		exit(-1);
	}

	std::vector<Flower *> a11(v5());
	std::vector<int> r11({ 3, 4, 5, 1, 2 });
	s = 2; e = 2;
	reorderFlowers(a11, s, e);
	if (!(eq(a11, r11) && (s == 0) && (e == 0))) {
		exit(-1);
	}

	std::vector<Flower *> a12(v5());
	std::vector<int> r12({ 1, 2, 3, 4, 5 });
	s = 0; e = 4;
	reorderFlowers(a12, s, e);
	if (!(eq(a12, r12) && (s == 0) && (e == 4))) {
		exit(-1);
	}

	std::vector<Flower *> a13(v5());
	std::vector<int> r13({ 5, 4, 3, 2, 1 });
	s = 4; e = 0;
	reorderFlowers(a13, s, e);
	if (!(eq(a13, r13) && (s == 0) && (e == 4))) {
		exit(-1);
	}

	std::vector<Flower *> a14(v5());
	std::vector<int> r14({ 5, 4, 3, 2, 1 });
	s = 4; e = 2;
	reorderFlowers(a14, s, e);
	if (!(eq(a14, r14) && (s == 0) && (e == 2))) {
		exit(-1);
	}

	std::vector<Flower *> a15(v5());
	std::vector<int> r15({ 2, 3, 4, 5, 1 });;
	s = 1; e = 3;
	reorderFlowers(a15, s, e);
	if (!(eq(a15, r15) && (s == 0) && (e == 2))) {
		exit(-1);
	}

	std::vector<Flower *> a16(v5());
	std::vector<int> r16({ 2, 3, 4, 5, 1 });;
	s = 1; e = 0;
	reorderFlowers(a16, s, e);
	if (!(eq(a16, r16) && (s == 0) && (e == 4))) {
		exit(-1);
	}
}

void setBlockingEdgeToRegular(Flower *flowerA, Flower *flowerB)
{
	STD_VECTOR_FOREACH_(Edge *, flowerA->edges, edgeIt, edgeEnd) {
		Edge *edge(*edgeIt);
		bool isConnectedToPrevSubFlower((edge->type == Edge::Type::FULL_BLOCKING)
			&& (std::find(edge->flowers.begin(), edge->flowers.end(), flowerB) != edge->flowers.end()));
		if (isConnectedToPrevSubFlower) {
			edge->type = Edge::Type::REGULAR;
		}
	}
}

void executeBurstFlower(Flower *greenFlower)
{
	// Find the subflower that connects to the parent.
	Flower *upperSubFlower(nullptr);
	{
		// Find the edge that connects to the parent.
		Edge *parentEdge(nullptr);
		STD_VECTOR_FOREACH_(Edge *, greenFlower->parent->edges, edgeIt, edgeEnd) {
			Edge *edge(*edgeIt);

			if (edge->type == Edge::Type::FULL_BLOCKING) {
				const std::vector<Flower *> &edgeFlowers(edge->flowers);
				if (std::find(edgeFlowers.begin(), edgeFlowers.end(), greenFlower) != edgeFlowers.end()) {
					parentEdge = edge;
					break;
				}
			}
		}
		const std::vector<Flower *> &parentEdgeFlowers(parentEdge->flowers);

		// Find the subflower that connects to the edge that connects to the parent.
		STD_VECTOR_FOREACH_(Flower *, greenFlower->subFlowers, flowerIt, flowerEnd) {
			upperSubFlower = *flowerIt;
			if (std::find(parentEdgeFlowers.begin(), parentEdgeFlowers.end(), upperSubFlower) != parentEdgeFlowers.end()) {
				break;
			}
		}
	}

	// Find the subflower that contains the stem vertex.
	Flower *lowerSubFlower(greenFlower->stemSubFlower);
	
	// Initialize variables for sub flower reordering.
	std::vector<Flower *> greenFlowerSubFlowers(greenFlower->subFlowers);	

	int upperSubFlowerId(0);
	int lowerSubFlowerId(0);
	int subFlowersCount(static_cast<int>(greenFlowerSubFlowers.size()));

	// Find the indices of the upper and lower subflowers.
	for (int i(0); i < subFlowersCount; ++i) {
		if (greenFlowerSubFlowers[i] == upperSubFlower) {
			upperSubFlowerId = i;
		}
		if (greenFlowerSubFlowers[i] == lowerSubFlower) {
			lowerSubFlowerId = i;
		}
	}
	
	// Reorder green subflowers.
	// The first flower becomes the upper subflower, then follows an odd number of flowers,
	// then follows the lower subflower, then follows an even number of flowers.
	reorderFlowers(greenFlowerSubFlowers, upperSubFlowerId, lowerSubFlowerId);

	// Replace the green flower in the connection with its parent by the upper sub flower.
	{
		// Remove the green flower from its parent's children.
		std::vector<Flower *> &parentChildren(greenFlower->parent->children);
		parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), greenFlower), parentChildren.end());

		// Add the upper sub flower to the parent's children.
		parentChildren.push_back(upperSubFlower);

		// Set the green flower's parent as the upper sub flower's parent.
		upperSubFlower->parent = greenFlower->parent;
	}

	// Replace the green flower in the connection with its child by the lower sub flower.
	{
		Flower *greenFlowerChild(greenFlower->children.front());
		
		// Set the lower sub flower as the parent of the green flower's child.
		greenFlowerChild->parent = lowerSubFlower;

		// Set the green flower's child as the lower sub flower's child.
		lowerSubFlower->children.push_back(greenFlowerChild);
	}

	// Process the segment of subflowers that remains in the tree.
	for (int i(upperSubFlowerId), count(lowerSubFlowerId + 1); i < count; ++i) {
		Flower *subFlower(greenFlowerSubFlowers[i]);

		subFlower->type = ((i % 2) == 0) ? Flower::Type::ODD_IN_TREE: Flower::Type::EVEN_IN_TREE;		
		if (subFlower->parent == nullptr) {
			subFlower->parent = greenFlowerSubFlowers[i - 1];
		}
		if (subFlower->children.empty()) {
			subFlower->children.push_back(greenFlowerSubFlowers[i + 1]);
		}
	}

	// Process all subflowers that become Dumbbells.
	for (int i(lowerSubFlowerId + 1); i < subFlowersCount; ++i) {
		greenFlowerSubFlowers[i]->type = Flower::Type::IN_DUMBBELL;
	}

	// Set blocking edges at the beginning and end of the tree segments as regular.
	setBlockingEdgeToRegular(upperSubFlower, greenFlowerSubFlowers[subFlowersCount - 1]);
	setBlockingEdgeToRegular(lowerSubFlower, greenFlowerSubFlowers[(lowerSubFlowerId + 1) % subFlowersCount]);

	// Remove the green flower from all edges.
	STD_VECTOR_FOREACH_(Edge *, greenFlower->edges, edgeIt, edgeEnd) {
		std::vector<Flower *> &edgeFlowers((*edgeIt)->flowers);
		edgeFlowers.erase(std::remove(edgeFlowers.begin(), edgeFlowers.end(), greenFlower), edgeFlowers.end());
	}
}

void executeAppendDumbbell(Edge *minEdge, std::vector<Flower *> &freeFlowers)
{
	minEdge->type = Edge::Type::FULL_BLOCKING;

	// Determine the tree flower and the upper Dumbbell flower.
	Flower* treeFlower(freeFlowers.front());
	Flower* upperDumbbellFlower(freeFlowers.back());
	if (treeFlower->isInDumbbell()) {
		std::swap(treeFlower, upperDumbbellFlower);
	}

	// Set parameters for the upper Dumbbell flower.
	treeFlower->children.push_back(upperDumbbellFlower);
	upperDumbbellFlower->parent = treeFlower;
	upperDumbbellFlower->type = Flower::Type::ODD_IN_TREE;

	// Determine the lower Dumbbell flower.
	std::vector<Flower *> dumbbellFreeFlowers(upperDumbbellFlower->inPairingEdge()->freeFlowers());
	Flower *lowerDumbbellFlower(dumbbellFreeFlowers.front());
	if (lowerDumbbellFlower == upperDumbbellFlower) {
		lowerDumbbellFlower = dumbbellFreeFlowers.back();
	}

	// Set parameters for the lower Dumbbell flower.
	upperDumbbellFlower->children.push_back(lowerDumbbellFlower);
	lowerDumbbellFlower->parent = upperDumbbellFlower;
	lowerDumbbellFlower->type = Flower::Type::EVEN_IN_TREE;
}

Flower *executeCreateFlower(Edge *minEdge, std::vector<Flower *> &freeFlowers)
{
	minEdge->type = Edge::Type::FULL_BLOCKING;

	// Determine K flower's path to root.
	std::vector<Flower*> kPathToRoot;
	for (Flower *kFlower(freeFlowers.front()); kFlower != nullptr; kFlower = kFlower->parent) {
		kPathToRoot.push_back(kFlower);
	}

	// Determine H flower's path to root.
	std::vector<Flower*> hPathToRoot;
	for (Flower *hFlower(freeFlowers.back()); hFlower != nullptr; hFlower = hFlower->parent) {
		hPathToRoot.push_back(hFlower);
	}

	// Find the W flower, which is the LCA of K flower and H flower.
	Flower *wFlower(nullptr);
	std::vector<Flower*>::reverse_iterator kRIt(kPathToRoot.rbegin()), hRIt(hPathToRoot.rbegin()),
		kREnd(kPathToRoot.rend()), hREnd(hPathToRoot.rend());
	for (; (kRIt != kREnd) && (hRIt != hREnd); ++kRIt, ++hRIt) {
		if (*kRIt != *hRIt) {
			break;
		}
		wFlower = *kRIt;
	}

	// Create and initialize Z flower, which is the new flower.
	Flower *zFlower(new Flower());
	zFlower->parent = wFlower->parent;
	zFlower->stemSubFlower = wFlower;

	// Replace W flower with Z flower in Z flower's parent.
	if (zFlower->parent != nullptr) {
		std::vector<Flower *> &parentChildren(zFlower->parent->children);
		parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), wFlower), parentChildren.end());
		parentChildren.push_back(zFlower);
	}

	// Populate subflowers of Z flower in the following order W, K_p, ..., K_1, K, H, H_1, ..., H_q.
	zFlower->subFlowers.push_back(wFlower);
	for (; kRIt != kREnd; ++kRIt) {
		zFlower->subFlowers.push_back(*kRIt);
	}
	for (std::vector<Flower*>::iterator hIt(hPathToRoot.begin()); *hIt != wFlower; ++hIt) {
		zFlower->subFlowers.push_back(*hIt);
	}

	// Populate children and edges of Z flower.
	std::vector<Flower *> zBlueFlowers(zFlower->blueSubFlowers());
	STD_VECTOR_FOREACH_(Flower *, zFlower->subFlowers, subFlowerIt, subFlowerEnd) {
		Flower *subFlower(*subFlowerIt);
		
		// Add the children of subflowers into Z flower's children only if the child is not part of Z flower.
		STD_VECTOR_FOREACH_(Flower *, subFlower->children, childFlowerIt, childFlowerEnd) {
			Flower *childFlower(*childFlowerIt);
			if (std::find(zBlueFlowers.begin(), zBlueFlowers.end(), childFlower->blueStem()) == zBlueFlowers.end()) {
				zFlower->children.push_back(childFlower);
			}
		}
		
		// Add the edges of subflowers into Z flower's edges only if the edge is outgoing from Z flower.
		STD_VECTOR_FOREACH_(Edge *, subFlower->edges, subEdgeIt, subEdgeEnd) {
			Edge *subEdge(*subEdgeIt);			
			
			bool areBothEdgeBlueFlowersInZFlower(
				std::find(zBlueFlowers.begin(), zBlueFlowers.end(), subEdge->blueFlowers.front()) != zBlueFlowers.end()
				&& std::find(zBlueFlowers.begin(), zBlueFlowers.end(), subEdge->blueFlowers.back()) != zBlueFlowers.end());

			if (!areBothEdgeBlueFlowersInZFlower) {
				zFlower->edges.push_back(subEdge);
				subEdge->flowers.push_back(zFlower);
			}
		}
	}

	// Replace parent in the new children of Z Flower.
	STD_VECTOR_FOREACH_(Flower *, zFlower->children, flowerIt, flowerEnd) {
		(*flowerIt)->parent = zFlower;
	}


	// Set subflower parameters.
	STD_VECTOR_FOREACH_(Flower *, zFlower->subFlowers, flowerIt, flowerEnd) {
		Flower *subflower(*flowerIt);
		subflower->type = Flower::Type::INTERNAL;
		subflower->parent = nullptr;
		subflower->children.clear();
	}

	return zFlower;
}

std::vector<Edge *> preprocessAlternatingPathEdges(Flower *flower, Edge *outgoingEdge)
{
	std::vector<Edge *> pathEdges;

	if (!flower->subFlowers.empty()) {
		std::vector<Flower *> subFlowers(flower->subFlowers);

		// Find outgoing sub flower.
		Flower *outgoingSubFlower(nullptr);
		STD_VECTOR_FOREACH_(Flower *, subFlowers, flowerIt, flowerEnd) {
			Flower *subFlower(*flowerIt);
			if (std::find(subFlower->edges.begin(), subFlower->edges.end(), outgoingEdge) != subFlower->edges.end()) {
				outgoingSubFlower = subFlower;
				break;
			}
		}
		
		// Initialize variables for sub flower reordering.
		int stemSubFlowerId(0);
		int outgoingSubFlowerId(0);
		int subFlowersCount(static_cast<int>(subFlowers.size()));

		// Find the indices of the stem and outgoing subflowers.
		for (int i(0); i < subFlowersCount; ++i) {
			if (subFlowers[i] == flower->stemSubFlower) {
				stemSubFlowerId = i;
			}
			if (subFlowers[i] == outgoingSubFlower) {
				outgoingSubFlowerId = i;
			}
		}

		// Reorder subflowers.
		// The first flower becomes the stem subflower, then follows an odd number of flowers,
		// then follows the outgoing subflower, then follows an even number of flowers.
		reorderFlowers(subFlowers, stemSubFlowerId, outgoingSubFlowerId);

		for (int i(0); i < outgoingSubFlowerId; i += 2) {
			Flower *flowerA(subFlowers[i]);
			Flower *flowerB(subFlowers[i + 1]);

			// Find outgoing sub edge.
			Edge *outgoingSubEdge(nullptr);
			STD_VECTOR_FOREACH_(Edge *, flowerA->edges, edgeIt, edgeEnd) {
				Edge *edge(*edgeIt);
				if (edge->type == Edge::Type::FULL_BLOCKING) {
					if (std::find(edge->flowers.begin(), edge->flowers.end(), flowerB) != edge->flowers.end()) {
						outgoingSubEdge = edge;
						break;
					}
				}
			}

			// Append edges within flower A.
			std::vector<Edge *> subPathEdgesA(preprocessAlternatingPathEdges(flowerA, outgoingSubEdge));
			pathEdges.insert(pathEdges.end(), subPathEdgesA.begin(), subPathEdgesA.end());

			// Append edge between flower A and B.
			pathEdges.push_back(outgoingSubEdge);

			// Append edges within flower B.
			std::vector<Edge *> subPathEdgesB(preprocessAlternatingPathEdges(flowerB, outgoingSubEdge));
			pathEdges.insert(pathEdges.end(), subPathEdgesB.begin(), subPathEdgesB.end());

			// Append pairing edge outgoing from flower B.
			pathEdges.push_back(flowerB->blueStem()->inPairingEdge());
		}

		// Append edges within the last flower.
		std::vector<Edge *> lastSubPathEdges(preprocessAlternatingPathEdges(subFlowers[outgoingSubFlowerId], outgoingEdge));
		pathEdges.insert(pathEdges.end(), lastSubPathEdges.begin(), lastSubPathEdges.end());
		
		// Set new stem subflower.
		flower->stemSubFlower = outgoingSubFlower;
	}

	return pathEdges;
}

void dismantleTree(Flower *flower)
{
	STD_VECTOR_FOREACH_(Flower *, flower->children, subFlowerIt, subFlowerEnd) {
		dismantleTree(*subFlowerIt);
	}

	flower->type = Flower::Type::IN_DUMBBELL;
	flower->parent = nullptr;
	flower->children.clear();
}

void swapBlockingAndInPairningEdgeType(Edge *edge)
{
	if (edge->type == Edge::Type::FULL_BLOCKING) {
		edge->type = Edge::Type::FULL_IN_PAIRING;
	} else if (edge->type == Edge::Type::FULL_IN_PAIRING) {
		edge->type = Edge::Type::FULL_BLOCKING;
	}
}

void executeCollapseTree(Edge *minEdge, std::vector<Flower *> &freeFlowers)
{
	minEdge->type = Edge::Type::FULL_IN_PAIRING;

	for (int i(0); i < VERTEX_PER_EDGE_COUNT; ++i) {
		Flower* freeFlower(freeFlowers[i]);
		Edge *outgoingEdge(minEdge);

		FOREVER {
			// Process the alternating path of the even flower.
			{
				std::vector<Edge *> alternatingPathEdges(preprocessAlternatingPathEdges(freeFlower, outgoingEdge));
				STD_VECTOR_FOREACH_(Edge *, alternatingPathEdges, edgeIt, edgeEnd) {
					swapBlockingAndInPairningEdgeType(*edgeIt);
				}
			}

			// Exit the loop if the even flower doesn't have an odd parent.
			if (freeFlower->parent == nullptr) {
				break;
			}
			freeFlower = freeFlower->parent;

			// Swap the type of the in pairing edge.
			freeFlower->inPairingEdge()->type = Edge::Type::FULL_BLOCKING;

			// Find and swap the type of the outgoing edge of the odd flower.			
			STD_VECTOR_FOREACH_(Edge *, freeFlower->parent->edges, edgeIt, edgeEnd) {
				outgoingEdge = *edgeIt;
				bool isBlockingParentEdge((outgoingEdge->type == Edge::Type::FULL_BLOCKING)
					&& (std::find(outgoingEdge->flowers.begin(), outgoingEdge->flowers.end(), freeFlower) != outgoingEdge->flowers.end()));
				if (isBlockingParentEdge) {
					outgoingEdge->type = Edge::Type::FULL_IN_PAIRING;
					break;
				}
			}

			// Process the alternation path of the odd flower.
			{
				std::vector<Edge *> alternatingPathEdges(preprocessAlternatingPathEdges(freeFlower, outgoingEdge));
				STD_VECTOR_FOREACH_(Edge *, alternatingPathEdges, edgeIt, edgeEnd) {
					swapBlockingAndInPairningEdgeType(*edgeIt);
				}
			}

			// Loop iteration step.
			freeFlower = freeFlower->parent;			
		}
		
		// Recursively dismantle the tree into dumbbells.
		dismantleTree(freeFlower);
	}
}