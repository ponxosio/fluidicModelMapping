#include "fluidicmodelmapping.h"

FluidicModelMapping::FluidicModelMapping(std::shared_ptr<FluidicMachineModel> model)
{
    this->model = model;
}

FluidicModelMapping::~FluidicModelMapping() {
}

bool FluidicModelMapping::areCompatible(
        std::shared_ptr<ProtocolGraph> graph,
        std::shared_ptr<ProtocolSimulatorInterface> simulator)
throw(std::invalid_argument)
{
    AnalysisExecutor protocolAnalysis(graph, simulator, model->getDefaultRate() * model->getDefaultRateUnits());

    //checkForCompatiblePumps(protocolAnalysis.getFlowsInTime()); flows can be with variables (unknow value, better not check)

    std::shared_ptr<HeuristicInterface> heuristic =
            std::make_shared<TopologyHeuristic>(model->getMachineGraph(), protocolAnalysis.getVCVector());
    AStarSearch search(model, heuristic, protocolAnalysis.getVCVector(), protocolAnalysis.getFlowsInTime());
    bool finded = search.startSearch();

    if (finded) {
        relation.clear();
        for(const auto & actualPair: *search.getRelationTable().begin()) {
            relation.insert(actualPair);
        }
    }
    return finded;
}

int FluidicModelMapping::getMappedComponent(const string & virtualContainer) throw(std::invalid_argument) {
    auto finded = relation.find(virtualContainer);
    if (finded != relation.end()) {
        return finded->second;
    } else {
        throw(std::invalid_argument("FluidicModelMapping::getMappedComponent. " + virtualContainer + " is not on relation table"));
    }
}

void FluidicModelMapping::checkForCompatiblePumps(const std::vector<MachineFlowStringAdapter::FlowsVector> & flowsInTime) {
    model->clearDisabledPumps();

    const std::shared_ptr<const MachineGraph> machinePtr = model->getMachineGraph();

    for(const auto & actualFlow : flowsInTime) {
        for(const auto & actualPair: actualFlow) {
            units::Volumetric_Flow flowRate = std::get<1>(actualPair);

            for(int pumpId : machinePtr->getPumpsIdsSet()) {
                std::shared_ptr<FluidicMachineNode> pumpPtr = machinePtr->getNode(pumpId);
                if (!pumpPtr->inWorkingRange(Function::pump, 1, flowRate)) {
                    model->disablePump(pumpId);
                }
            }
        }
    }
}
