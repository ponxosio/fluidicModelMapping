#ifndef TOPOLOGYHEURISTIC_H
#define TOPOLOGYHEURISTIC_H

#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <fluidicmachinemodel/machinegraph.h>
#include <fluidicmachinemodel/fluidicnode/containernode.h>

#include "fluidicmodelmapping/heuristic/containercharacteristics.h"
#include "fluidicmodelmapping/heuristic/heuristicinterface.h"

#include "fluidicmodelmapping/fluidicmodelmapping_global.h"

class TOPOLOGYHEURISTIC_EXPORT TopologyHeuristic : public HeuristicInterface
{
public:
    TopologyHeuristic(std::shared_ptr<const MachineGraph> machinePtr, const std::vector<ContainerCharacteristics> & protocolCharacts);
    virtual ~TopologyHeuristic();

    virtual double evaluateNode(const SearchNode & node, std::vector<int> & compatibleNodes);

protected:
    std::unordered_map<int,ContainerCharacteristics> machineContainerCharacteristics;
    std::vector<ContainerCharacteristics> protocolContainerCharacteristics;

    void analyzeMachine(std::shared_ptr<const MachineGraph> machinePtr);
    ContainerCharacteristics analyzeContainer(const std::shared_ptr<ContainerNode> & containerPtr);
    int countContainersConnected(int id, std::shared_ptr<const MachineGraph> machinePtr);

    int getContainerSimilarityIndex(const ContainerCharacteristics & container1, const ContainerCharacteristics & container2);

    std::unordered_set<int> getUsedMachineContainers(int lastMappedContainer, const std::vector<int> & mappedContainers);
    void getCompatibleMachineContainers(const ContainerCharacteristics & protocolCharact,
                                        const std::unordered_set<int> & usedMachineContainers,
                                        std::vector<int> & compatibleContainers);


};

#endif // TOPOLOGYHEURISTIC_H
