#ifndef MACHINEFLOWADAPTER_H
#define MACHINEFLOWADAPTER_H

#include <algorithm>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

//local
#include <fluidicmachinemodel/machine_graph_utils/machineflow.h>

#include <utils/memento.h>
#include <utils/units.h>

#include "fluidicmodelmapping/fluidicmodelmapping_global.h"

class MACHINEFLOWSTRINGADAPTER_EXPORT MachineFlowStringAdapter
{
public:
    typedef std::tuple<std::deque<std::string>,units::Volumetric_Flow> PathRateTuple;
    typedef std::vector<PathRateTuple> FlowsVector;

    static bool flowsVectorEquals(const FlowsVector & f1, const FlowsVector & f2);

    MachineFlowStringAdapter();
    MachineFlowStringAdapter(const MachineFlowStringAdapter & mfsa);
    virtual ~MachineFlowStringAdapter();

    void addFlow(const std::string & idSource, const std::string & idTarget, units::Volumetric_Flow rate);
    void removeFlow(const std::string & idSource, const std::string & idTarget);
    const FlowsVector & updateFlows();

    std::string flowToStr() const;

    inline void clear() {
        machineFlow.clear();
        conversionVector.clear();
    }

    inline std::shared_ptr<Memento<MachineFlowStringAdapter>> createMemento() const {
        return std::make_shared<Memento<MachineFlowStringAdapter>>(*this);
    }

    inline void restoreMemento(const Memento<MachineFlowStringAdapter> & memento) {
        restoreState(memento.getState());
    }

protected:
    MachineFlow machineFlow;
    std::vector<std::string> conversionVector;
    FlowsVector actualFlows;

    int getConvertedId(const std::string & id);
    const std::string & getConvertedId(int id);

    PathRateTuple translatePathTuple(const MachineFlow::PathRateTuple & intTuple);
    MachineFlow::PathRateTuple translatePathTuple(const PathRateTuple & strTuple);

    void restoreState(const MachineFlowStringAdapter & state);
};

#endif // MACHINEFLOWADAPTER_H
