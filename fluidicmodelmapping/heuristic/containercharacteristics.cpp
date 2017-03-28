#include "containercharacteristics.h"

ContainerCharacteristics::ContainerCharacteristics() {
    containerName = "Unknow";
    this->neccesaryFunctionsMask = 0;
    this->type = ContainerNode::unknow;
}

ContainerCharacteristics::ContainerCharacteristics(const std::string & virtualContainerName) :
    containerName(virtualContainerName)
{
    this->neccesaryFunctionsMask = 0;
    this->type = ContainerNode::unknow;
}

ContainerCharacteristics::~ContainerCharacteristics() {

}

void ContainerCharacteristics::addMustConnectVector(const std::vector<std::string> & container2connect) {
    mustConnectToVector.push_back(std::vector<std::string>(container2connect));
}

void ContainerCharacteristics::copyConnectionVector(const ConnectionVector & connectionVector) {
    mustConnectToVector.clear();
    mustConnectToVector.reserve(connectionVector.size());

    for(int i = 0; i < mustConnectToVector.size(); i++) {
        std::vector<std::string> elementCopys;
        elementCopys.reserve(connectionVector[i].size());
        for(int j=0; j < connectionVector[i].size(); j++) {
            std::string actualEcopy(connectionVector[i][j]);
            elementCopys.insert(elementCopys.begin() + j, actualEcopy);
        }
        mustConnectToVector.insert(mustConnectToVector.begin() + i, elementCopys);
    }
}
