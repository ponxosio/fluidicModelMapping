#include "solutioncheck.h"

bool SolutionCheck::isSolution(std::shared_ptr<FluidicMachineModel> fluidicModel,
                               const SearchInterface::RelationTable & mappedContainers,
                               const std::vector<MachineFlowStringAdapter::FlowsVector> & flowsInTime)
{
    bool solution = true;
    for(auto it = flowsInTime.begin(); solution && it != flowsInTime.end(); ++it) {
        MachineFlow::FlowsVector machineFlows = translateFlows(*it, mappedContainers);
        solution = fluidicModel->checkFlows(machineFlows);
    }
    return solution;
}

MachineFlow::FlowsVector SolutionCheck::translateFlows(const MachineFlowStringAdapter::FlowsVector & flowsInTime,
                                                       const SearchInterface::RelationTable & mappedContainers)
{
    MachineFlow::FlowsVector translated;
    translated.reserve(flowsInTime.size());

    for(int i = 0; i < flowsInTime.size(); i++) {
        const std::deque<string> & strFlow = std::get<0>(flowsInTime[i]);
        const units::Volumetric_Flow & units = std::get<1>(flowsInTime[i]);

        std::deque<short int> intFlow;
        for(const std::string & actualContainer: strFlow) {
            intFlow.push_back(mappedContainers.at(actualContainer));
        }
        translated.insert(translated.begin() + i, std::make_tuple(intFlow, units));
    }
    return translated;
}