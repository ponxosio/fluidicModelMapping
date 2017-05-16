#include "searchnode.h"
#include "fluidicmodelmapping/heuristic/heuristicinterface.h"

SearchNode::SearchNode(int lastMappedContainer,
           const std::vector<int> & mappedContainers,
           std::shared_ptr<HeuristicInterface> heuristic) :
    mappedContainers(mappedContainers)
{
    this->lastMappedContainer = lastMappedContainer;
    this->heuristicValue = heuristic->evaluateNode(*this, compatibleNodesNextContainer);
}

SearchNode::SearchNode(const SearchNode & node) :
    compatibleNodesNextContainer(node.compatibleNodesNextContainer), mappedContainers(node.mappedContainers)
{
    this->lastMappedContainer = node.lastMappedContainer;
    this->heuristicValue = node.heuristicValue;
}

SearchNode::~SearchNode() {

}
