#include "containercharacteristics.h"

ContainerCharacteristics::ContainerCharacteristics() {
    containerName = "Unknow";
    this->neccesaryFunctionsMask = 0;
    this->type = ContainerNode::unknow;
    this->arrivingConnections = 0;
    this->leavingConnections = 0;
}

ContainerCharacteristics::ContainerCharacteristics(const ContainerCharacteristics & cc) :
    containerName(cc.containerName),
    neccesaryFunctionsMask(cc.neccesaryFunctionsMask),
    workingRangeMap(cc.workingRangeMap)
{
    this->arrivingConnections = cc.arrivingConnections;
    this->leavingConnections = cc.leavingConnections;
    this->type = cc.type;
}

ContainerCharacteristics::ContainerCharacteristics(const std::string & virtualContainerName) :
    containerName(virtualContainerName)
{
    this->neccesaryFunctionsMask = 0;
    this->type = ContainerNode::unknow;
    this->arrivingConnections = 0;
    this->leavingConnections = 0;
}

ContainerCharacteristics::~ContainerCharacteristics() {

}

bool ContainerCharacteristics::compatible(const ContainerCharacteristics & containerChar) const {
    return (this->type == containerChar.type) &&
           ((this->neccesaryFunctionsMask & containerChar.neccesaryFunctionsMask) == containerChar.neccesaryFunctionsMask) &&
           (areWorkingRangeMapsCompatible(containerChar.workingRangeMap)) &&
           ((this->arrivingConnections + this->leavingConnections) >= (containerChar.arrivingConnections + containerChar.leavingConnections));
}

void ContainerCharacteristics::addFunctions(Function::OperationType op) {
    int pos = (int) op;
    neccesaryFunctionsMask[pos] = 1;
}

void ContainerCharacteristics::addFunctions(const FunctionsBitSet & functions) {
    neccesaryFunctionsMask |= functions;
}

void ContainerCharacteristics::addWorkingRange(Function::OperationType op, const std::shared_ptr<const ComparableRangeInterface> workingRange)
    throw(std::invalid_argument)
{
    auto finded = workingRangeMap.find(op);
    if (finded != workingRangeMap.end()) {
        throw(std::invalid_argument("ContainerCharacteristics::addWorkingRange. " + std::to_string((int) op) + " op has alreadya  range set"));
    } else {
        workingRangeMap.insert(std::make_pair(op, workingRange));
    }
}

bool ContainerCharacteristics::areWorkingRangeMapsCompatible(const WorkingRangeMap & othermap) const {
    bool compatible = true;
    for(auto it = workingRangeMap.begin(); (compatible && (it != workingRangeMap.end())); ++it) {
        Function::OperationType actualType = it->first;

        auto finded = othermap.find(actualType);
        if (finded != othermap.end()) {
            const std::shared_ptr<const ComparableRangeInterface> myWorkingRange = it->second;
            const std::shared_ptr<const ComparableRangeInterface> otherWorkingRange = finded->second;
            compatible = myWorkingRange->compatible(otherWorkingRange);
        } else {
            compatible = false;
        }
    }
    return compatible;
}
