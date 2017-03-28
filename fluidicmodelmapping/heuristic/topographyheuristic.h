#ifndef TOPOGRAPHYHEURISTIC_H
#define TOPOGRAPHYHEURISTIC_H

#include "fluidicmodelmapping/heuristic/heuristicinterface.h"

class TopographyHeuristic : public HeuristicInterface
{
public:
    TopographyHeuristic();
    virtual ~TopographyHeuristic();

    std::vector<int> orderAvailableNodes(const ContainerCharacteristics & virtualContainer, const std::vector<int> availableNodes);
};

#endif // TOPOGRAPHYHEURISTIC_H
