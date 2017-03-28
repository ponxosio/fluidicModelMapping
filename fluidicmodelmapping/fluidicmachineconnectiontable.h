#ifndef FLUIDICMACHINECONNECTIONTABLE_H
#define FLUIDICMACHINECONNECTIONTABLE_H

#include <memory>
#include <vector>

#include <fluidicmachinemodel/machinegraph.h>

class FluidicMachineConnectionTable
{
    typedef std::vector<std::vector<int>> ConnectionTable;

public:
    FluidicMachineConnectionTable(std::shared_ptr<MachineGraph> machineGraph);
    virtual ~FluidicMachineConnectionTable();

    bool areConnected(unsigned int source, unsigned int target);
    bool areConnected(unsigned int source, const std::vector<unsigned int> & targets);

    int connectedCloseContainers(unsigned int source);
    int connectedOpenContainers(unsigned int source);

protected:
    ConnectionTable connectionTable;

    void analyzeGraph(std::shared_ptr<MachineGraph> MachineGraph);
};

#endif // FLUIDICMACHINECONNECTIONTABLE_H
