#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H

#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include <fluidicmachinemodel/fluidicmachinemodel.h>

#include "fluidicmodelmapping/heuristic/containercharacteristics.h"
#include "fluidicmodelmapping/heuristic/heuristicinterface.h"
#include "fluidicmodelmapping/searchalgorithms/searchinterface.h"
#include "fluidicmodelmapping/searchalgorithms/searchnode.h"
#include "fluidicmodelmapping/searchalgorithms/solutioncheck.h"

#include "fluidicmodelmapping/fluidicmodelmapping_global.h"

class ASTARSEARCH_EXPORT AStarSearch : public SearchInterface
{

public:
    AStarSearch(std::shared_ptr<FluidicMachineModel> fluidicModel,
                std::shared_ptr<HeuristicInterface> heuristic,
                const std::vector<ContainerCharacteristics> & virtualContainerVector,
                const std::vector<MachineFlowStringAdapter::FlowsVector> & flowsInTime);
    virtual ~AStarSearch();

    virtual bool startSearch();

protected:
    typedef std::priority_queue<SearchNode, std::vector<SearchNode>, SearchNode::SearchNodeCompareFunct> SearchNodeHeap;

    std::shared_ptr<HeuristicInterface> heuristicPtr;
    std::shared_ptr<FluidicMachineModel> fluidicModelPtr;
    std::vector<ContainerCharacteristics> virtualContainerVector;
    std::vector<MachineFlowStringAdapter::FlowsVector> flowsInTime;

    SearchNodeHeap nodesHeap;

    RelationTable translateSolution(const std::vector<int> & mappedNodes);
    void expandNode(const SearchNode & node);

};

#endif // ASTARSEARCH_H
