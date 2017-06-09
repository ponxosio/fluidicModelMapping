#ifndef FLUIDICMODELMAPPING_H
#define FLUIDICMODELMAPPING_H

#include <cstdarg>
#include <memory>
#include <stdexcept>

#include <bioblocksTranslation/logicblocksmanager.h>
#include <commonmodel/mappinginterface/mappinginterface.h>
#include <fluidicmachinemodel/fluidicmachinemodel.h>

#include <protocolGraph/execution_interface/protocolsimulationinterface.h>
#include <protocolGraph/ProtocolGraph.h>

#include "fluidicmodelmapping/heuristic/topologyheuristic.h"
#include "fluidicmodelmapping/protocolAnalysis/analysisexecutor.h"
#include "fluidicmodelmapping/searchalgorithms/astarsearch.h"

#include "fluidicmodelmapping/fluidicmodelmapping_global.h"

class FLUIDICMODELMAPPINGSHARED_EXPORT FluidicModelMapping : public MappingInterface
{
public:
    FluidicModelMapping(std::shared_ptr<FluidicMachineModel> model);
    virtual ~FluidicModelMapping();

    virtual bool findRelation(std::shared_ptr<ProtocolSimulatorInterface> simulator,
                              std::string & errorMsg) throw(std::invalid_argument);
    virtual int getMappedComponent(const string &virtualContainer) throw(std::invalid_argument);

protected:
    SearchInterface::RelationTable relation;
    std::shared_ptr<FluidicMachineModel> model;

    void checkForCompatiblePumps(const std::vector<MachineFlowStringAdapter::FlowsVector> & flowsInTime);
};

#endif // FLUIDICMODELMAPPING_H
