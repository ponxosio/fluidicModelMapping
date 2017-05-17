#include "containercharacteristicsexecutor.h"

ContainerCharacteristicsExecutor::ContainerCharacteristicsExecutor(units::Volumetric_Flow defaultRate)
{
    this->defaultRate = defaultRate;
}

ContainerCharacteristicsExecutor::~ContainerCharacteristicsExecutor() {

}

void ContainerCharacteristicsExecutor::applyLigth(const std::string & sourceId, units::Length wavelength, units::LuminousIntensity intensity) {
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::apply_light);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    workingRange.setLigthWorkingRange(intensity, wavelength);
}

void ContainerCharacteristicsExecutor::applyTemperature(const std::string & sourceId, units::Temperature temperature) {
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::heat);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    workingRange.setHeaterWorkingRange(temperature);
}

void ContainerCharacteristicsExecutor::stir(const std::string & idSource, units::Frequency intensity) {
    ContainerCharacteristics & cCh = getContainerCharacteristics(idSource);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::stir);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(idSource);
    workingRange.setStirerWorkingRange(intensity);
}

void ContainerCharacteristicsExecutor::centrifugate(const std::string & idSource, units::Frequency intensity) {
    ContainerCharacteristics & cCh = getContainerCharacteristics(idSource);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::centrifugate);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(idSource);
    workingRange.setCentrifugerWorkingRange(intensity);
}

void ContainerCharacteristicsExecutor::shake(const std::string & idSource, units::Frequency intensity) {
    ContainerCharacteristics & cCh = getContainerCharacteristics(idSource);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::shake);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(idSource);
    workingRange.setShakerWorkingRange(intensity);
}

void ContainerCharacteristicsExecutor::startElectrophoresis(const std::string & idSource, units::ElectricField fieldStrenght) {
    ContainerCharacteristics & cCh = getContainerCharacteristics(idSource);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::electrophoresis);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(idSource);
    workingRange.setElectrophorerWorkingRange(fieldStrenght);
}

units::Volume ContainerCharacteristicsExecutor::getVirtualVolume(const std::string & sourceId) {
    getContainerCharacteristics(sourceId);
    return -1 * units::ml;
}

void ContainerCharacteristicsExecutor::loadContainer(
        const std::string & sourceId,
        units::Volume initialVolume)
{
    getContainerCharacteristics(sourceId);
}

void ContainerCharacteristicsExecutor::startMeasureOD(
        const std::string & sourceId,
        units::Frequency measurementFrequency,
        units::Length wavelength)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::measure_od);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    workingRange.setOdSensorWorkingRange(wavelength);
}

void ContainerCharacteristicsExecutor::startMeasureTemperature(
        const std::string & sourceId,
        units::Frequency measurementFrequency)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::measure_temperature);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    workingRange.setTemperatureSensorWorkingRange();
}

void ContainerCharacteristicsExecutor::startMeasureLuminiscense(
        const std::string & sourceId,
        units::Frequency measurementFrequency)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::measure_luminiscence);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    workingRange.setLuminiscenceSensorWorkingRange();
}

void ContainerCharacteristicsExecutor::startMeasureVolume(
        const std::string & sourceId,
        units::Frequency measurementFrequency)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::measure_volume);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    workingRange.setVolumeSensorWorkingRange();
}

void ContainerCharacteristicsExecutor::startMeasureFluorescence(
        const std::string & sourceId,
        units::Frequency measurementFrequency,
        units::Length excitation,
        units::Length emission)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::measure_fluorescence);
    cCh.addFunctions(mask);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    workingRange.setFluorescenceSensorWorkingRange(emission, excitation);
}

void ContainerCharacteristicsExecutor::setContinuosFlow(
        const std::string & idSource,
        const std::string & idTarget,
        units::Volumetric_Flow rate)
{
    machineFlow.addFlow(idSource, idTarget, rate);
}

void ContainerCharacteristicsExecutor::stopContinuosFlow(const std::string & idSource, const std::string & idTarget) {
    machineFlow.removeFlow(idSource, idTarget);
}

units::Time ContainerCharacteristicsExecutor::transfer(
        const std::string & idSource,
        const std::string & idTarget,
        units::Volume volume)
{
    machineFlow.addFlow(idSource, idTarget, defaultRate);
    return timeSlice*2;
}

void ContainerCharacteristicsExecutor::stopTransfer(const std::string & idSource, const std::string & idTarget) {
    machineFlow.removeFlow(idSource, idTarget);
}

units::Time ContainerCharacteristicsExecutor::mix(
        const std::string & idSource1,
        const std::string & idSource2,
        const std::string & idTarget,
        units::Volume volume1,
        units::Volume volume2)
{
    units::Time duration = transfer(idSource1, idTarget, volume1);
    transfer(idSource2, idTarget, volume2);
    return duration;
}

void ContainerCharacteristicsExecutor::stopMix(
        const std::string & idSource1,
        const std::string & idSource2,
        const std::string & idTarget)
{
    stopTransfer(idSource1, idTarget);
    stopTransfer(idSource2, idTarget);
}

void ContainerCharacteristicsExecutor::setTimeStep(units::Time time) {
    timeSlice = time;
}

units::Time ContainerCharacteristicsExecutor::timeStep() {
    const MachineFlowStringAdapter::FlowsVector & flowsVector = machineFlow.updateFlows();
    analyzeFlowInTime(flowsVector);
    flowsInTime.push_back(flowsVector);

    return timeSlice;
}

void ContainerCharacteristicsExecutor::analyzeFlowInTime(const MachineFlowStringAdapter::FlowsVector & flows) throw(std::invalid_argument) {
    std::hash<std::string> strHash;
    for(const auto & actualItem : flows) {
        const std::deque<std::string> & containersQueue = std::get<0>(actualItem);

        if (containersQueue.size() > 1) {
            auto it = containersQueue.begin();
            std::string lastId = *it;
            ++it;

            for(;it != containersQueue.end(); ++it) {
                const std::string & actualId = *it;

                std::size_t sourceId = strHash(lastId);
                std::size_t targetId = strHash(actualId);

                connectionGraph.addNode(std::make_shared<Node>(sourceId));
                connectionGraph.addNode(std::make_shared<Node>(targetId));

                if (!connectionGraph.areConnected(sourceId, targetId)) {
                    connectionGraph.addEdge(std::make_shared<Edge>(sourceId, targetId));
                }
            }
        } else {
            throw(std::invalid_argument(
                        "ContainerCharacteristicsExecutor::analyzeFlowInTime. Containers queue in flows in time vector is not at least of size 2"));
        }
    }
}

ContainerCharacteristics & ContainerCharacteristicsExecutor::getContainerCharacteristics(const std::string & sourceId) {
    auto finded = vcCharacteristicsMap.find(sourceId);
    if (finded != vcCharacteristicsMap.end()) {
        return finded->second;
    } else {
        ContainerCharacteristics newCCh(sourceId);
        vcCharacteristicsMap.insert(std::make_pair(sourceId,newCCh));

        return vcCharacteristicsMap[sourceId];
    }
}

WorkingRangeManager & ContainerCharacteristicsExecutor::getContainerWorkingRange(const std::string & sourceId) {
    auto finded = vcWorkingrangeMap.find(sourceId);
    if (finded != vcWorkingrangeMap.end()) {
        return finded->second;
    } else {
        WorkingRangeManager newWR;
        vcWorkingrangeMap.insert(std::make_pair(sourceId,newWR));

        return vcWorkingrangeMap[sourceId];
    }
}
