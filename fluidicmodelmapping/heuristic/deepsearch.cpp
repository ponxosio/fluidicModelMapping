#include "deepsearch.h"

DeepSearch::DeepSearch(FluidicMachineModel* modelPtr,
                       const std::vector<ContainerCharacteristics> & virtualContainers,
                       const std::vector<MachineFlow::FlowsVector> & flowsInTime) :
    virtualContainerVector(virtualContainers), flowsInTime(flowsInTime)
{
    this->modelPtr = modelPtr;
    fillRelationTable(virtualContainers);
}

DeepSearch::~DeepSearch() {

}

bool DeepSearch::startSearch() {
    relationsVector.clear();
    clearRelationTable();
    startSearch_recursive(0);

    return !relationsVector.empty();
}

void DeepSearch::startSearch_recursive(int actualIndex) {
    if (actualIndex < virtualContainerVector.size()) {
        const ContainerCharacteristics & actualCharacteristics = virtualContainerVector[actualIndex];
        std::vector<int> nodes2check = availableNodes(actualCharacteristics);

        for(auto it = nodes2check.begin(); it != nodes2check.end(); ++it) {
            int id2Map = *it;
            addRelation(actualCharacteristics, id2Map);
            startSearch_recursive(actualIndex + 1);
            removeRelation(actualCharacteristics);
        }
    } else {
        if (isRelationCorrect()) {
            relationsVector.push_back(relationTable);
        }
    }
}

void DeepSearch::clearRelationTable() {
    for(auto it = relationTable.begin(); it != relationTable.end(); ++it) {
        it->second = -1;
    }
}

void DeepSearch::fillRelationTable(const std::vector<ContainerCharacteristics> & virtualContainers) {
    for(const ContainerCharacteristics & characteristic: virtualContainers) {
        relationTable[characteristic.getName()] = -1;
    }
}

void DeepSearch::addRelation(const ContainerCharacteristics & containerCharact, int machineNodeId) {
    relationTable[containerCharact.getName()] = machineNodeId;
    alreadyMappedIds.insert(machineNodeId);
}

void DeepSearch::removeRelation(const ContainerCharacteristics & containerCharact) {
    int lastMappedId = relationTable[containerCharact.getName()];
    alreadyMappedIds.erase(alreadyMappedIds.find(lastMappedId));
    relationTable[containerCharact.getName()] = -1;
}

bool DeepSearch::isRelationCorrect() {
    /*TODO:*/
    return false;
}

std::vector<int> DeepSearch::availableNodes(const ContainerCharacteristics & containerCharact) throw(std::invalid_argument) {
    if (containerCharact.getType() == ContainerNode::open) {
        return filterFunction(containerCharact.getNeccesaryFunctionsMask(), modelPtr->getMachineGraph()->getOpenContainersIdsSet());
    } else if (containerCharact.getType() == ContainerNode::close) {
        return filterFunction(containerCharact.getNeccesaryFunctionsMask(), modelPtr->getMachineGraph()->getCloseContainersIdsSet());
    } else {
        throw(std::invalid_argument(std::to_string((int) containerCharact.getType()) + " unknow type"));
    }
}

std::vector<int> DeepSearch::filterFunction(unsigned long functionsMask, const std::unordered_set<int> & containerSet) {
    std::vector<int> compatibleIds;
    for(int id : containerSet) {
        if ((alreadyMappedIds.find(id) == alreadyMappedIds.end()) &&
            (modelPtr->getComponent(id)->canDoOperations(functionsMask)))
        {
            compatibleIds.push_back(id);
        }
    }
    return compatibleIds;
}



































