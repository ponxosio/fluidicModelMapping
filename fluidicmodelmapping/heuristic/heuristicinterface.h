#ifndef HEURISTICINTERFACE_H
#define HEURISTICINTERFACE_H

#include <vector>
#include <tuple>

#include "fluidicmodelmapping/searchalgorithms/searchnode.h"

class HeuristicInterface
{
public:
    virtual ~HeuristicInterface(){}

    virtual double evaluateNode(const SearchNode & node, std::vector<int> & compatibleNodes) = 0;
};

#endif // HEURISTICINTERFACE_H
