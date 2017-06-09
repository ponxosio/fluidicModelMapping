#ifndef DEEPSEARCH_H
#define DEEPSEARCH_H

#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include <fluidicmachinemodel/fluidicmachinemodel.h>
#include <utils/machineflow.h>

#include "fluidicmodelmapping/heuristic/containercharacteristics.h"
#include "fluidicmodelmapping/heuristic/heuristicinterface.h"
#include "fluidicmodelmapping/searchalgorithms/searchinterface.h"

class DeepSearch : public SearchInterface
{

public:
    DeepSearch(FluidicMachineModel* modelPtr,
               const std::vector<ContainerCharacteristics> & virtualContainerVector,
               const std::vector<MachineFlow::FlowsVector> & flowsInTime);
    virtual ~DeepSearch();

    virtual bool startSearch(std::string & errorMsg);

protected:
    FluidicMachineModel* modelPtr;
    std::vector<ContainerCharacteristics> virtualContainerVector;
    std::vector<MachineFlow::FlowsVector> flowsInTime;

    RelationTable relationTable;
    std::unordered_set<int> alreadyMappedIds;

    void startSearch_recursive(int actualIndex);

    void clearRelationTable();
    void fillRelationTable(const std::vector<ContainerCharacteristics> & virtualContainerVector);
    void addRelation(const ContainerCharacteristics & containerCharact, int machineNodeId);
    void removeRelation(const ContainerCharacteristics & containerCharact);

    bool isRelationCorrect();

    std::vector<int> availableNodes(const ContainerCharacteristics & containerCharact) throw(std::invalid_argument);
    std::vector<int> filterFunction(const ContainerCharacteristics::FunctionsBitSet & functionsMask, const std::unordered_set<int> & containerSet);
};

#endif // DEEPSEARCH_H
