#include "Actions.h"

#include "Types.h"
#include "Utility.h"

#include <algorithm>
#include <vector>

#if VERTEX_PER_EDGE_COUNT!=2
CREATE A COMPILATION ERROR
#endif

void executeBurstFlower(const Flower *greenFlower)
{
	// Remove the green flower from all edges.
	STD_VECTOR_CONST_FOREACH_(Edge *, greenFlower->edges, edgeIt, edgeEnd) {
		std::vector<Flower *> &edgeFlowers((*edgeIt)->flowers);
		edgeFlowers.erase(std::remove(edgeFlowers.begin(), edgeFlowers.end(), greenFlower), edgeFlowers.end());
	}

	// Find the subflower that contains the stem vertex.
	Flower *lowerSubflower(greenFlower->stem);

	// Replace the green flower in its parent.

	// Replace the green flower in its child.
	STD_VECTOR_CONST_FOREACH_(Flower *, greenFlower->edges, edgeIt, edgeEnd) {
		std::vector<Flower *> &edgeFlowers((*edgeIt)->flowers);
		edgeFlowers.erase(std::remove(edgeFlowers.begin(), edgeFlowers.end(), greenFlower), edgeFlowers.end());
	}

	// Remove the 

	

	// Replace the parent in the green flower's M edge's adjacent flowers with the lower subflower.
	// This includes the green flower and its relevant subflowers as well as  itself and direct descendants 
	STD_VECTOR_CONST_FOREACH_(Flower *, greenFlower->mEdge->flowers, flowerIt, edgeEnd) {
	}

	// Find the subflower that connects to the parent.
	Flower *upperSubflower(nullptr);
	STD_VECTOR_CONST_FOREACH_(Flower *, greenFlower->subFlowers, flowerIt, flowerEnd) {
		upperSubflower = *flowerIt;

		if (greenFlower->parent == upperSubflower->parent) {
			break;
		}
	}

	// Make all subflowers in the odd length trail into dumbells.


}

void executeAppendDumbell(Edge *minEdge, std::vector<Flower *> &freeFlowers)
{
	minEdge->type = Edge::Type::L_FULL;

	// Determine the tree flower and the upper dumbell flower.
	Flower* treeFlower(freeFlowers[0]);
	Flower* upperDumbellFlower(freeFlowers[1]);
	if (treeFlower->isDumbell()) {
		std::swap(treeFlower, upperDumbellFlower);
	}

	// Set parameters for the upper dumbell flower.
	treeFlower->children.push_back(upperDumbellFlower);
	upperDumbellFlower->parent = treeFlower;
	upperDumbellFlower->type = Flower::Type::TREE_ODD;

	// Determine the lower dumbell flower.
	std::vector<Flower *> dumbellFreeFlowers(upperDumbellFlower->mEdge()->freeFlowers());
	Flower *lowerDumbellFlower(dumbellFreeFlowers[0]);
	if (lowerDumbellFlower == upperDumbellFlower) {
		lowerDumbellFlower = dumbellFreeFlowers[1];
	}

	// Set parameters for the lower dumbell flower.
	upperDumbellFlower->children.push_back(lowerDumbellFlower);
	lowerDumbellFlower->parent = upperDumbellFlower;
	lowerDumbellFlower->type = Flower::Type::TREE_EVEN;
}

Flower *executeCreateFlower(Edge *minEdge, std::vector<Flower *> &freeFlowers)
{
	minEdge->type = Edge::Type::L_FULL;

	// Determine K flower's path to root.
	std::vector<Flower*> kPathToRoot;
	kPathToRoot.push_back(freeFlowers[0]);
	while (kPathToRoot.back()->parent != nullptr) {
		kPathToRoot.push_back(kPathToRoot.back()->parent);
	}

	// Determine H flower's path to root.
	std::vector<Flower*> hPathToRoot;
	hPathToRoot.push_back(freeFlowers[1]);
	while (hPathToRoot.back()->parent != nullptr) {
		hPathToRoot.push_back(hPathToRoot.back()->parent);
	}

	// Find the W flower, which is the LCA of K flower and H flower.
	Flower *wFlower(nullptr);
	std::vector<Flower*>::reverse_iterator kRIt, hRIt;
	for (kRIt = kPathToRoot.rbegin(), hRIt = hPathToRoot.rbegin(); *kRIt == *hRIt; ++kRIt, ++hRIt) {
		wFlower = *kRIt;
	}

	// Create and initialize Z flower, which is the new flower.
	Flower *zFlower(new Flower());
	zFlower->parent = wFlower->parent;
	zFlower->stem = wFlower;

	// Populate subflowers of Z flower in the following order W, K_p, ..., K_1, K, H, H_1, ..., H_q.
	zFlower->subFlowers.push_back(wFlower);
	for (std::vector<Flower*>::reverse_iterator kREnd(kPathToRoot.rend()); kRIt != kREnd; ++kRIt) {
		zFlower->subFlowers.push_back(*kRIt);
	}
	for (std::vector<Flower*>::iterator hIt(hPathToRoot.begin()); *hIt != wFlower; ++hIt) {
		zFlower->subFlowers.push_back(*kRIt);
	}

	// Populate children and edges of Z flower.
	std::vector<Flower *> zBlueFlowers(zFlower->blueSubFlowers());
	STD_VECTOR_CONST_FOREACH_(Flower *, zFlower->subFlowers, subFlowerIt, subFlowerEnd) {
		const Flower *subFlower(*subFlowerIt);
		
		STD_VECTOR_CONST_FOREACH_(Flower *, subFlower->children, childFlowerIt, childFlowerEnd) {
			Flower *childFlower(*childFlowerIt);
			if (std::find(zBlueFlowers.begin(), zBlueFlowers.end(), childFlower->blueStem()) == zBlueFlowers.end()) {
				zFlower->children.push_back(childFlower);
			}
		}
		
		STD_VECTOR_CONST_FOREACH_(Edge *, subFlower->edges, subEdgeIt, subEdgeEnd) {
			Edge *subEdge(*subEdgeIt);			
			
			bool areBothEdgeBlueFlowersInZFlower(
				std::find(zBlueFlowers.begin(), zBlueFlowers.end(), subEdge->blueFlowers[0]) != zBlueFlowers.end()
				&& std::find(zBlueFlowers.begin(), zBlueFlowers.end(), subEdge->blueFlowers[1]) != zBlueFlowers.end());

			if (!areBothEdgeBlueFlowersInZFlower) {
				zFlower->edges.push_back(subEdge);
				subEdge->flowers.push_back(zFlower);
			}
		}
	}

	return zFlower;
}

void executeCollapseTree(Edge *minEdge, std::vector<Flower *> &freeFlowers)
{
	minEdge->type = Edge::Type::M_FULL;


}