#ifndef ANALYSISEXECUTOR_H
#define ANALYSISEXECUTOR_H

#include <functional>
#include <memory>
#include <stdexcept>

#include <protocolGraph/ProtocolGraph.h>
#include <utils/units.h>

#include "fluidicmodelmapping/protocolAnalysis/containercharacteristicsexecutor.h"

#include "fluidicmodelmapping/fluidicmodelmapping_global.h"

class ANALYSISEXECUTOR_EXPORT AnalysisExecutor
{
public:
    AnalysisExecutor(std::shared_ptr<ProtocolGraph> protocol, units::Volumetric_Flow defaultUnits) throw(std::invalid_argument);
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

    void analyzeProtocol(std::shared_ptr<ProtocolGraph> protocol, ContainerCharacteristicsExecutor* executor);
    void processResults(ContainerCharacteristicsExecutor* executor) throw(std::invalid_argument);

    void addArrivingLeavingConnections(const Graph<Node,Edge> & graph,
                                       ContainerCharacteristics & container) throw(std::invalid_argument);
    void addWorkingRanges(const std::unordered_map<std::string, WorkingRangeManager> & workingRangeMap,
                          ContainerCharacteristics & container) throw(std::invalid_argument);
};

#endif // ANALYSISEXECUTOR_H
