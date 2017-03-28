#include "fluidicmachineconnectiontable.h"

FluidicMachineConnectionTable::FluidicMachineConnectionTable(std::shared_ptr<MachineGraph> machineGraph) {

}

FluidicMachineConnectionTable::~FluidicMachineConnectionTable() {

}

bool FluidicMachineConnectionTable::areConnected(unsigned int source, unsigned int target) {
    /* TODO:*/
    return true;
}

bool FluidicMachineConnectionTable::areConnected(unsigned int source, const std::vector<unsigned int> & targets) {
    /* TODO:*/
    return true;
}

int FluidicMachineConnectionTable::connectedCloseContainers(unsigned int source) {
    /* TODO:*/
    return -1;
}

int FluidicMachineConnectionTable::connectedOpenContainers(unsigned int source) {
    /* TODO:*/
    return -1;
}
