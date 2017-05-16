#ifndef MACHINEFLOWADAPTER_H
#define MACHINEFLOWADAPTER_H

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

//local
#include <utils/units.h>
#include <fluidicmachinemodel/machine_graph_utils/machineflow.h>

#include "fluidicmodelmapping/fluidicmodelmapping_global.h"

class MACHINEFLOWSTRINGADAPTER_EXPORT MachineFlowStringAdapter
{
public:
    typedef std::tuple<std::deque<std::string>,units::Volumetric_Flow> PathRateTuple;
    typedef std::vector<PathRateTuple> FlowsVector;

    static bool flowsVectorEquals(const FlowsVector & f1, const FlowsVector & f2);

    MachineFlowStringAdapter();
    virtual ~MachineFlowStringAdapter();

    void addFlow(const std::string & idSource, const std::string & idTarget, units::Volumetric_Flow rate);
    void removeFlow(const std::string & idSource, const std::string & idTarget);
    const FlowsVector & updateFlows();

    std::string flowToStr() const;

    inline void clear() {
        machineFlow.clear();
        conversionVector.clear();
    }

protected:
    MachineFlow machineFlow;
    std::vector<std::string> conversionVector;
    FlowsVector actualFlows;

    int getConvertedId(const std::string & id);
    const std::string & getConvertedId(int id);

    PathRateTuple translatePathTuple(const MachineFlow::PathRateTuple & intTuple);
    MachineFlow::PathRateTuple translatePathTuple(const PathRateTuple & strTuple);
};

#endif // MACHINEFLOWADAPTER_H
