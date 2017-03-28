#include "machineflowstringadapter.h"

bool MachineFlowStringAdapter::flowsVectorEquals(const FlowsVector & f1, const FlowsVector & f2) {
    bool equals = (f1.size() == f2.size());
    for(auto it = f1.begin(); equals && it != f1.end(); ++it) {
        equals = (std::find(f2.begin(), f2.end(), *it) != f2.end());
    }
    return equals;
}

MachineFlowStringAdapter::MachineFlowStringAdapter() {

}

MachineFlowStringAdapter::~MachineFlowStringAdapter() {

}

void MachineFlowStringAdapter::addFlow(const std::string & idSource, const std::string & idTarget, units::Volumetric_Flow rate) {
    machineFlow.addFlow(getConvertedId(idSource), getConvertedId(idTarget), rate);
}

void MachineFlowStringAdapter::removeFlow(const std::string & idSource, const std::string & idTarget) {
    machineFlow.removeFlow(getConvertedId(idSource), getConvertedId(idTarget));
}

const MachineFlowStringAdapter::FlowsVector & MachineFlowStringAdapter::updateFlows() {
    actualFlows.clear();
    const MachineFlow::FlowsVector & intFlowsVector = machineFlow.updateFlows();

    actualFlows.reserve(intFlowsVector.size());
    for(const MachineFlow::PathRateTuple & intTuple: intFlowsVector) {
        actualFlows.push_back(translatePathTuple(intTuple));
    }
    return actualFlows;
}

std::string MachineFlowStringAdapter::flowToStr() {
    std::stringstream stream;

    stream << "[";
    for(const PathRateTuple & actualTuple: actualFlows) {
        const std::deque<string> & actualQueue = std::get<0>(actualTuple);
        stream << "[";
        for(const std::string & queueStr: actualQueue) {
            stream << queueStr;
        }
        const units::Volumetric_Flow & flow = std::get<1>(actualTuple);
        stream << ":" << flow.to(units::ml / units::hr) << "ml/hr],";
    }
    stream << "]";
    return stream.str();
}

int MachineFlowStringAdapter::getConvertedId(const std::string & id) {
    auto it = find(conversionVector.begin(),conversionVector.end(), id);
    if (it != conversionVector.end()) {
        return distance(conversionVector.begin(), it);
    } else {
        int newPos = conversionVector.size();
        conversionVector.push_back(id);
        return newPos;
    }
}

const std::string & MachineFlowStringAdapter::getConvertedId(int id) {
    return conversionVector[id];
}

MachineFlowStringAdapter::PathRateTuple MachineFlowStringAdapter::translatePathTuple(const MachineFlow::PathRateTuple & intTuple) {
    std::deque<string> transQue;
    for(int id: std::get<0>(intTuple)) {
        transQue.push_back(getConvertedId(id));
    }
    return std::make_tuple(transQue, std::get<1>(intTuple));
}












