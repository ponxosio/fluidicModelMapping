#ifndef HEURISTICINTERFACE_H
#define HEURISTICINTERFACE_H

#include <vector>

#include "fluidicmodelmapping/heuristic/containercharacteristics.h"

class HeuristicInterface
{
public:
    virtual ~HeuristicInterface(){}

    virtual std::vector<int> orderAvailableNodes(const ContainerCharacteristics & virtualContainer, const std::vector<int> availableNodes) = 0;
};

#endif // HEURISTICINTERFACE_H
