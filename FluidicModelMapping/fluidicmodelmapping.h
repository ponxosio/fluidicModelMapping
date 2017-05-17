#ifndef FLUIDICMODELMAPPING_H
#define FLUIDICMODELMAPPING_H

#include <memory>

#include <commonmodel/mappinginterface/mappinginterface.h>
#include <fluidicmachinemodel/fluidicmachinemodel.h>
#include <protocolGraph/ProtocolGraph.h>

#include "fluidicmodelmapping/heuristic/topologyheuristic.h"
#include "fluidicmodelmapping/protocolAnalysis/analysisexecutor.h"
#include "fluidicmodelmapping/searchalgorithms/astarsearch.h"

class FluidicModelMapping : public MappingInterface
{
public:
    FluidicModelMapping(std::shared_ptr<FluidicMachineModel> model);
    virtual ~FluidicModelMapping();

    virtual bool areCompatible(std::shared_ptr<ProtocolGraph> graph);
    virtual int getMappedComponent(const string &virtualContainer) throw(std::invalid_argument);

protected:
    SearchInterface::RelationTable relation;
    std::shared_ptr<FluidicMachineModel> model;

    void checkForCompatiblePumps(const std::vector<MachineFlowStringAdapter::FlowsVector> & flowsInTime);
};

#endif // FLUIDICMODELMAPPING_H
