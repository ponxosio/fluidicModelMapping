#include "astarsearch.h"

AStarSearch::AStarSearch(
        std::shared_ptr<FluidicMachineModel> fluidicModel,
        std::shared_ptr<HeuristicInterface> heuristic,
        const std::vector<ContainerCharacteristics> & virtualContainerVector,
        const std::vector<MachineFlowStringAdapter::FlowsVector> & flowsInTime) :
    SearchInterface(), virtualContainerVector(virtualContainerVector), flowsInTime(flowsInTime)
{
    this->fluidicModelPtr = fluidicModel;
    this->heuristicPtr = heuristic;
}

AStarSearch::~AStarSearch() {

}

bool AStarSearch::startSearch() {
    bool solutionFinded = false;

    std::vector<int> mappedContainers(virtualContainerVector.size(), -1);
    SearchNode initNode(-1, mappedContainers, heuristicPtr);

    nodesHeap.push(initNode);
    while(!solutionFinded && !nodesHeap.empty()) {
        SearchNode node2process(nodesHeap.top());
        nodesHeap.pop();

        if (node2process.isSolutionCandidate()) {
            RelationTable solution = translateSolution(node2process.getMappedContainers());
            if (solutionFinded = SolutionCheck::isSolution(fluidicModelPtr, solution, flowsInTime)) {
                relationsVector.push_back(solution);
            }
        } else {
            expandNode(node2process);
        }
    }
    return solutionFinded;
}

void AStarSearch::expandNode(const SearchNode & node) {
    int lastMappedContainer = node.getLastMappedContainer();
    for(int compatibleNode : node.getCompatibleNextContainer()) {
        std::vector<int> mappedContainersCopy(node.getMappedContainers());
        mappedContainersCopy[lastMappedContainer + 1] = compatibleNode;

        SearchNode newNode(lastMappedContainer + 1, mappedContainersCopy, heuristicPtr);
        nodesHeap.push(newNode);
    }
}

SearchInterface::RelationTable AStarSearch::translateSolution(const std::vector<int> & mappedNodes) {
    RelationTable table;
    for(int i = 0; i < mappedNodes.size(); i++) {
        const std::string & protocolContainer = virtualContainerVector[i].getName();
        int machineContainer = mappedNodes[i];
        table.insert(std::make_pair(protocolContainer, machineContainer));
    }
    return table;
}
