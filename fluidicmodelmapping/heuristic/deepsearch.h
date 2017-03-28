#ifndef DEEPSEARCH_H
#define DEEPSEARCH_H

#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "fluidicmachinemodel/fluidicmachinemodel.h"
#include "fluidicmachinemodel/machine_graph_utils/machineflow.h"

#include "fluidicmodelmapping/heuristic/containercharacteristics.h"
#include "fluidicmodelmapping/heuristic/heuristicinterface.h"

class DeepSearch
{
public:
    typedef std::unordered_map<std::string, int> RelationTable;

    DeepSearch(FluidicMachineModel* modelPtr,
               const std::vector<ContainerCharacteristics> & virtualContainerVector,
               const std::vector<MachineFlow::FlowsVector> & flowsInTime);
    virtual ~DeepSearch();

    bool startSearch();

    inline const std::vector<RelationTable> & getRelationTable() const {
        return relationsVector;
    }
protected:
    FluidicMachineModel* modelPtr;
    std::vector<ContainerCharacteristics> virtualContainerVector;
    std::vector<MachineFlow::FlowsVector> flowsInTime;

    RelationTable relationTable;
    std::vector<RelationTable> relationsVector;
    std::unordered_set<int> alreadyMappedIds;

    void startSearch_recursive(int actualIndex);

    void clearRelationTable();
    void fillRelationTable(const std::vector<ContainerCharacteristics> & virtualContainerVector);
    void addRelation(const ContainerCharacteristics & containerCharact, int machineNodeId);
    void removeRelation(const ContainerCharacteristics & containerCharact);

    bool isRelationCorrect();

    std::vector<int> availableNodes(const ContainerCharacteristics & containerCharact) throw(std::invalid_argument);
    std::vector<int> filterFunction(unsigned long functionsMask, const std::unordered_set<int> & containerSet);
};

#endif // DEEPSEARCH_H
