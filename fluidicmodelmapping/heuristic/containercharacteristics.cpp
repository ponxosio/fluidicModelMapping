#include "containercharacteristics.h"

ContainerCharacteristics::ContainerCharacteristics() {
    containerName = "Unknow";
    this->neccesaryFunctionsMask = 0;
    this->type = ContainerNode::unknow;
    this->numberConnections = 0;
    this->minCapacity = 0 * units::ml;
}

ContainerCharacteristics::ContainerCharacteristics(const ContainerCharacteristics & cc) :
    containerName(cc.containerName),
    neccesaryFunctionsMask(cc.neccesaryFunctionsMask),
    workingRangeMap(cc.workingRangeMap)
{
    this->numberConnections = cc.numberConnections;
    this->type = cc.type;
    this->minCapacity = cc.minCapacity;
}

ContainerCharacteristics::ContainerCharacteristics(const std::string & virtualContainerName) :
    containerName(virtualContainerName)
{
    this->neccesaryFunctionsMask = 0;
    this->type = ContainerNode::unknow;
    this->numberConnections = 0;
    this->minCapacity = 0 * units::ml;
}

ContainerCharacteristics::~ContainerCharacteristics() {

}

bool ContainerCharacteristics::compatible(const ContainerCharacteristics & containerChar) const {
    bool compatible1 = (containerChar.type == ContainerNode::unknow || this->type == containerChar.type) &&
                       (this->minCapacity >= containerChar.minCapacity) &&
                       (this->numberConnections >= containerChar.numberConnections);

    bool compatible2 = areWorkingRangeMapsCompatible(containerChar.workingRangeMap);
    bool compatible3 = (this->neccesaryFunctionsMask & containerChar.neccesaryFunctionsMask) == containerChar.neccesaryFunctionsMask;

    return compatible1 && compatible2 && compatible3;
}

void ContainerCharacteristics::addFunctions(Function::OperationType op) {
    int pos = (int) op;
    neccesaryFunctionsMask.set(pos);
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
    for(auto it = othermap.begin(); (compatible && (it != othermap.end())); ++it) {
        Function::OperationType actualType = it->first;

        auto finded = workingRangeMap.find(actualType);
        if (finded != workingRangeMap.end()) {
            const std::shared_ptr<const ComparableRangeInterface> myWorkingRange = finded->second;
            const std::shared_ptr<const ComparableRangeInterface> otherWorkingRange = it->second;
            compatible = myWorkingRange->compatible(otherWorkingRange);
        } else {
            compatible = false;
        }
    }
    return compatible;
}
