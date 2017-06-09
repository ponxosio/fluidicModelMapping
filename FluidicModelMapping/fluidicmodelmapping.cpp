#include "fluidicmodelmapping.h"

FluidicModelMapping::FluidicModelMapping(std::shared_ptr<FluidicMachineModel> model)
{
    this->model = model;
}

FluidicModelMapping::~FluidicModelMapping() {
}

bool FluidicModelMapping::findRelation(
        std::shared_ptr<ProtocolSimulatorInterface> simulator,
        std::string & errorMsg)
    throw(std::invalid_argument)
{
    AnalysisExecutor protocolAnalysis(simulator, model->getDefaultRate() * model->getDefaultRateUnits());

    checkForCompatiblePumps(protocolAnalysis.getFlowsInTime());

    std::vector<ContainerCharacteristics> vcVector = protocolAnalysis.getVCVector();

    std::sort(vcVector.begin(),
              vcVector.end(),
              ContainerCharacteristics::ContainerCharacteristicsComparator());

    std::shared_ptr<HeuristicInterface> heuristic =
            std::make_shared<TopologyHeuristic>(model->getMachineGraph(), vcVector);

    AStarSearch search(model, heuristic, vcVector, protocolAnalysis.getFlowsInTime());
    bool finded = search.startSearch(errorMsg);

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
