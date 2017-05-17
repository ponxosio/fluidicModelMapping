#include "topologyheuristic.h"

TopologyHeuristic::TopologyHeuristic(
        std::shared_ptr<const MachineGraph> machinePtr,
        const std::vector<ContainerCharacteristics> & protocolCharacts) :
    protocolContainerCharacteristics(protocolCharacts)
{
    std::sort(protocolContainerCharacteristics.begin(),
              protocolContainerCharacteristics.end(),
              ContainerCharacteristics::ContainerCharacteristicsComparator());
    analyzeMachine(machinePtr);
}

TopologyHeuristic::~TopologyHeuristic() {

}

double TopologyHeuristic::evaluateNode(const SearchNode & node, std::vector<int> & compatibleNodes) {
    double value = 0.0;

    int nodesMapped = node.getLastMappedContainer() + 1;
    const std::vector<int> & mappedContainers = node.getMappedContainers();

    int numberCompatibleContainer = 1;
    if (nodesMapped < mappedContainers.size()) {
        std::unordered_set<int> usedMachineContainers = getUsedMachineContainers(node.getLastMappedContainer(), mappedContainers);
        const ContainerCharacteristics & nextProtocolCChar = protocolContainerCharacteristics[nodesMapped];
        getCompatibleMachineContainers(nextProtocolCChar, usedMachineContainers, compatibleNodes);
        numberCompatibleContainer = (int)compatibleNodes.size();
    }

    if (nodesMapped > 0 && numberCompatibleContainer > 0) {
        const ContainerCharacteristics & actualProtocolCChar = protocolContainerCharacteristics[node.getLastMappedContainer()];
        const ContainerCharacteristics & machineCChar = machineContainerCharacteristics[mappedContainers[node.getLastMappedContainer()]];
        double mappedContainersSimilarity = getContainerSimilarityIndex(actualProtocolCChar, machineCChar);

        int maxB = (int)(protocolContainerCharacteristics.size() - 2);
        maxB = std::max(maxB, 1);

        value = mappedContainersSimilarity /
                (nodesMapped * std::min(numberCompatibleContainer, maxB));
    } else {
        value = std::numeric_limits<double>::max();
    }
    return value;
}

void TopologyHeuristic::analyzeMachine(std::shared_ptr<const MachineGraph> machinePtr) {
    for(int closeCId : machinePtr->getCloseContainersIdsSet()) {
        ContainerCharacteristics cc = analyzeContainer(machinePtr->getContainer(closeCId));
        cc.setLeavingConnections(machinePtr->getLeavingTubes(closeCId)->size());
        cc.setArrivingConnections(machinePtr->getArrivingTubes(closeCId)->size());
        machineContainerCharacteristics.insert(std::make_pair(closeCId, cc));
    }
    for(int openCId : machinePtr->getOpenContainersIdsSet()) {
        ContainerCharacteristics cc = analyzeContainer(machinePtr->getContainer(openCId));
        cc.setLeavingConnections(machinePtr->getLeavingTubes(openCId)->size());
        cc.setArrivingConnections(machinePtr->getArrivingTubes(openCId)->size());
        machineContainerCharacteristics.insert(std::make_pair(openCId, cc));
    }
}

ContainerCharacteristics TopologyHeuristic::analyzeContainer(const std::shared_ptr<ContainerNode> & containerPtr) {
    ContainerCharacteristics cc(std::to_string(containerPtr->getContainerId()));
    cc.setType(containerPtr->getContainerType());

    const std::bitset<Function::MAX_OPTYPE> & aceptedFunctions = containerPtr->getAvailableFunctions().getAceptedFunctions();
    cc.addFunctions(aceptedFunctions);

    for(int i = 0; i < Function::MAX_OPTYPE; i++) {
        if(aceptedFunctions.test(i)) {
            cc.addWorkingRange((Function::OperationType) i, containerPtr->getComparableWorkingRange((Function::OperationType) i));
        }
    }
    return cc;
}

int TopologyHeuristic::getContainerSimilarityIndex(const ContainerCharacteristics & container1, const ContainerCharacteristics & container2) {
    int value = 1;
    value += std::abs((int)(container1.getArrivingConnections() - container2.getArrivingConnections()));
    value += std::abs((int)(container1.getLeavingConnections() - container2.getLeavingConnections()));
    value += std::abs((int)(container1.getNeccesaryFunctionsMask().count() - container2.getNeccesaryFunctionsMask().count()));
    return value;
}

std::unordered_set<int> TopologyHeuristic::getUsedMachineContainers(int lastMappedContainer, const std::vector<int> & mappedContainers) {
    std::unordered_set<int> usedMachineC;
    for(int i = 0; i <= lastMappedContainer; i++) {
        usedMachineC.insert(mappedContainers[i]);
    }
    return usedMachineC;
}

void TopologyHeuristic::getCompatibleMachineContainers(const ContainerCharacteristics & protocolCharact,
                                                       const std::unordered_set<int> & usedMachineContainers,
                                                       std::vector<int> & compatibleContainers)
{
    for(const auto & pair : machineContainerCharacteristics) {
        int idContainer = pair.first;
        if (usedMachineContainers.find(idContainer) == usedMachineContainers.end()) {
            const ContainerCharacteristics & actualMCC = pair.second;
            if (actualMCC.compatible(protocolCharact)) {
                compatibleContainers.push_back(idContainer);
            }
        }
    }

}





















