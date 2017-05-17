#include "analysisexecutor.h"

AnalysisExecutor::AnalysisExecutor(
        std::shared_ptr<ProtocolGraph> protocol,
        units::Volumetric_Flow defaultUnits)
    throw(std::invalid_argument)
{
    ContainerCharacteristicsExecutor executor(defaultUnits);
    try {
        analyzeProtocol(protocol, &executor);
        processResults(&executor);
    } catch (std::exception & e) {
        throw(std::invalid_argument("AnalysisExecutor::AnalysisExecutor. " + std::string(e.what())));
    }
}

AnalysisExecutor::~AnalysisExecutor() {

}

void AnalysisExecutor::analyzeProtocol(std::shared_ptr<ProtocolGraph> protocol, ContainerCharacteristicsExecutor* executor) {
    std::vector<int> nodes2process = {protocol->getStart()->getContainerId()};
    while(!nodes2process.empty()) {
        int nextId = nodes2process.back();
        nodes2process.pop_back();

        if (protocol->isCpuOperation(nextId)) {
            protocol->getCpuOperation(nextId)->execute();
        } else if (protocol->isActuatorOperation(nextId)) {
            protocol->getActuatorOperation(nextId)->execute(executor);
        }

        ProtocolGraph::ProtocolEdgeVectorPtr leaving = protocol->getProjectingEdges(nextId);
        for(const ProtocolGraph::ProtocolEdgePtr & edge: *leaving.get()) {
            if (edge->isPhyscal() || edge->conditionMet()) {
                int nextop = edge->getIdTarget();
                if (find(nodes2process.begin(),nodes2process.end(), nextop) == nodes2process.end()) {
                    nodes2process.push_back(nextop);
                }
            }
        }
    }
}

void AnalysisExecutor::processResults(ContainerCharacteristicsExecutor* executor) throw(std::invalid_argument) {
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
        container.setArrivingConnections(graph.getArrivingEdges(id)->size());
        container.setLeavingConnections(graph.getLeavingEdges(id)->size());
    } else {
        throw(std::invalid_argument("AnalysisExecutor::addArrivingLeavingConnections. " + container.getName() + " is not on the graph"));
    }
}

void AnalysisExecutor::addWorkingRanges(
        const std::unordered_map<std::string, WorkingRangeManager> & workingRangeMap,
        ContainerCharacteristics & container)
    throw(std::invalid_argument)
{
    auto finded = workingRangeMap.find(container.getName());
    if (finded != workingRangeMap.end()) {
        const WorkingRangeManager & workingRange = finded->second;
        for(const auto & actualPair: workingRange.getWorkingRangeMap()) {
            Function::OperationType op = actualPair.first;
            const std::shared_ptr<const ComparableRangeInterface> workingRangePtr = actualPair.second;

            container.addWorkingRange(op, workingRangePtr);
        }
    } else {
        throw(std::invalid_argument("AnalysisExecutor::addWorkingRanges. " + container.getName() + " not present in workingRangeMap"));
    }
}



















