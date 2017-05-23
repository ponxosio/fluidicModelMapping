#ifndef SOLUTIONCHECK_H
#define SOLUTIONCHECK_H

#include <memory>
#include <vector>

#include <fluidicmachinemodel/fluidicmachinemodel.h>
#include <utils/machineflow.h>
#include <utils/machineflowstringadapter.h>

#include "fluidicmodelmapping/searchalgorithms/searchinterface.h"

class SolutionCheck
{
public:
    static bool isSolution(std::shared_ptr<FluidicMachineModel> fluidicModel,
                           const SearchInterface::RelationTable & mappedContainers,
                           const std::vector<MachineFlowStringAdapter::FlowsVector> & flowsInTime);

protected:
    static MachineFlow::FlowsVector translateFlows(const MachineFlowStringAdapter::FlowsVector & flowsInTime,
                                                   const SearchInterface::RelationTable & mappedContainers);
};

#endif // SOLUTIONCHECK_H
