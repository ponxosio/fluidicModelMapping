#ifndef ANALYSISEXECUTOR_H
#define ANALYSISEXECUTOR_H

#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_set>

#include <protocolGraph/ProtocolGraph.h>
#include <protocolGraph/ConditionEdge.h>
#include <protocolGraph/execution_interface/protocolsimulationinterface.h>

#include <utils/units.h>

#include "fluidicmodelmapping/protocolAnalysis/containercharacteristicsexecutor.h"
#include "fluidicmodelmapping/protocolAnalysis/protocolrunningsimulator.h"

#include "fluidicmodelmapping/fluidicmodelmapping_global.h"

class ANALYSISEXECUTOR_EXPORT AnalysisExecutor
{
public:
    AnalysisExecutor(std::shared_ptr<ProtocolGraph> protocol,
                     std::shared_ptr<ProtocolSimulatorInterface> simulator,
                     units::Volumetric_Flow defaultUnits) throw(std::invalid_argument);
    virtual ~AnalysisExecutor();

    inline const std::vector<ContainerCharacteristics> & getVCVector() const {
        return vcVector;
    }

    inline const std::vector<MachineFlowStringAdapter::FlowsVector> & getFlowsInTime() const {
        return flowsInTime;
    }

protected:
    std::vector<ContainerCharacteristics> vcVector;
    std::vector<MachineFlowStringAdapter::FlowsVector> flowsInTime;

    void processResults(std::shared_ptr<ContainerCharacteristicsExecutor> executor) throw(std::invalid_argument);
    void addArrivingLeavingConnections(const Graph<Node,Edge> & graph,
                                       ContainerCharacteristics & container) throw(std::invalid_argument);
    void addWorkingRanges(const std::unordered_map<std::string,
                          WorkingRangeManager> & workingRangeMap,
                          ContainerCharacteristics & container);
};

#endif // ANALYSISEXECUTOR_H
