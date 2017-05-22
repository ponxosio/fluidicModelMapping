#include "analysisexecutor.h"

AnalysisExecutor::AnalysisExecutor(
        std::shared_ptr<ProtocolGraph> protocol,
        std::shared_ptr<ProtocolSimulatorInterface> simulator,
        units::Volumetric_Flow defaultUnits)
    throw(std::invalid_argument)
{
    std::shared_ptr<ContainerCharacteristicsExecutor> executor = std::make_shared<ContainerCharacteristicsExecutor>(defaultUnits);
    try {
        simulator->simulateProtocol(protocol, executor);
        processResults(executor);
    } catch (std::exception & e) {
        throw(std::invalid_argument("AnalysisExecutor::AnalysisExecutor. " + std::string(e.what())));
    }
}

AnalysisExecutor::~AnalysisExecutor() {

}

void AnalysisExecutor::processResults(std::shared_ptr<ContainerCharacteristicsExecutor> executor) throw(std::invalid_argument) {
    const std::vector<MachineFlowStringAdapter::FlowsVector> & actualFlowsIntime = executor->getFlowsInTime();

    flowsInTime.reserve(actualFlowsIntime.size());
    for(const MachineFlowStringAdapter::FlowsVector & actualFlow: actualFlowsIntime) {
            MachineFlowStringAdapter::FlowsVector flowCopy(actualFlow);
            flowsInTime.push_back(flowCopy);
    }

    const std::unordered_map<std::string, ContainerCharacteristics> & vcCharacteristicsMap = executor->getVcCharacteristicsMap();
    const std::unordered_map<std::string, WorkingRangeManager> & vcWorkingrangeMap = executor->getVcWorkingrangeMap();
    const Graph<Node,Edge> & connectionGraph = executor->getConnectionGraph();

    vcVector.reserve(vcCharacteristicsMap.size());
    for(const auto & it : vcCharacteristicsMap) {
        ContainerCharacteristics ccCopy(it.second);

        addWorkingRanges(vcWorkingrangeMap, ccCopy);
        addArrivingLeavingConnections(connectionGraph, ccCopy);
        vcVector.push_back(ccCopy);
    }
}

void AnalysisExecutor::addArrivingLeavingConnections(
        const Graph<Node,Edge> & graph,
        ContainerCharacteristics & container)
    throw(std::invalid_argument)
{
    std::hash<std::string> strHash;
    std::size_t id = strHash(container.getName());

    const std::shared_ptr<Node> & nodePtr = graph.getNode(id);
    if(nodePtr != NULL) {
        int arrivingEdges = graph.getArrivingEdges(id)->size();
        int leavingEdges = graph.getLeavingEdges(id)->size();

        container.setArrivingConnections(arrivingEdges);
        container.setLeavingConnections(leavingEdges);

        if ((arrivingEdges == 0) || (leavingEdges == 0)) {
            container.setType(ContainerNode::open);
        } else {
            container.setType(ContainerNode::close);
        }
    }
}

void AnalysisExecutor::addWorkingRanges(
        const std::unordered_map<std::string, WorkingRangeManager> & workingRangeMap,
        ContainerCharacteristics & container)
{
    auto finded = workingRangeMap.find(container.getName());
    if (finded != workingRangeMap.end()) {
        const WorkingRangeManager & workingRange = finded->second;
        for(const auto & actualPair: workingRange.getWorkingRangeMap()) {
            Function::OperationType op = actualPair.first;
            const std::shared_ptr<const ComparableRangeInterface> workingRangePtr = actualPair.second;

            container.addWorkingRange(op, workingRangePtr);
        }
    }
}



















