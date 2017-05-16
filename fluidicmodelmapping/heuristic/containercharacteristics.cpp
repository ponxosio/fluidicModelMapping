#include "containercharacteristics.h"

ContainerCharacteristics::ContainerCharacteristics() {
    containerName = "Unknow";
    this->neccesaryFunctionsMask = 0;
    this->type = ContainerNode::unknow;
    this->arrivingConnections = 0;
    this->leavingConnections = 0;
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
           ((this->arrivingConnections + this->leavingConnections) >= (containerChar.arrivingConnections + containerChar.leavingConnections));
}

void ContainerCharacteristics::addFunctions(Function::OperationType op) {
    int pos = (int) op;
    neccesaryFunctionsMask[pos] = 1;
}

void ContainerCharacteristics::addFunctions(const FunctionsBitSet & functions) {
    neccesaryFunctionsMask |= functions;
}
