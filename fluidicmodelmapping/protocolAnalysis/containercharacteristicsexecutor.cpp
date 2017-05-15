#include "containercharacteristicsexecutor.h"

ContainerCharacteristicsExecutor::ContainerCharacteristicsExecutor()
{

}

ContainerCharacteristicsExecutor::~ContainerCharacteristicsExecutor() {

}

void ContainerCharacteristicsExecutor::applyLigth(const std::string & sourceId, units::Length wavelength, units::LuminousIntensity intensity) {
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::apply_light);
    cCh.addFunctions(mask);
}

void ContainerCharacteristicsExecutor::applyTemperature(const std::string & sourceId, units::Temperature temperature) {
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::heat);
    cCh.addFunctions(mask);
}

void ContainerCharacteristicsExecutor::stir(const std::string & idSource, units::Frequency intensity) {
    ContainerCharacteristics & cCh = getContainerCharacteristics(idSource);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::stir);
    cCh.addFunctions(mask);
}

void ContainerCharacteristicsExecutor::centrifugate(const std::string & idSource, units::Frequency intensity) {

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

double ContainerCharacteristicsExecutor::measureOD(
        const std::string & sourceId,
        units::Time duration,
        units::Frequency measurementFrequency,
        units::Length wavelength)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::measure_od);
    cCh.addFunctions(mask);
    return -1;
}

units::Temperature ContainerCharacteristicsExecutor::measureTemperature(
        const std::string & sourceId,
        units::Time duration,
        units::Frequency measurementFrequency)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::measure_temperature);
    cCh.addFunctions(mask);
    return -1 * units::C;
}

units::LuminousIntensity ContainerCharacteristicsExecutor::measureLuminiscense(
        const std::string & sourceId,
        units::Time duration,
        units::Frequency measurementFrequency)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::measure_luminousIntensity);
    cCh.addFunctions(mask);
    return -1 * units::cd;
}

units::Volume ContainerCharacteristicsExecutor::measureVolume(
        const std::string & sourceId,
        units::Time duration,
        units::Frequency measurementFrequency)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::measure_volume);
    cCh.addFunctions(mask);
    return -1 * units::ml;
}

units::LuminousIntensity ContainerCharacteristicsExecutor::measureFluorescence(
        const std::string & sourceId,
        units::Time duration,
        units::Frequency measurementFrequency)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    unsigned long mask = FunctionSet::FUNCTIONS_FLAG_MAP.at(Function::measure_fluorescence);
    cCh.addFunctions(mask);
    return -1 * units::cd;
}

void ContainerCharacteristicsExecutor::mix(
        const std::string & idSource1,
        const std::string & idSource2,
        const std::string & idTarget,
        units::Volume volume1,
        units::Volume volume2)
{


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

void ContainerCharacteristicsExecutor::transfer(
        const std::string & idSource,
        const std::string & idTarget,
        units::Volume volume)
{

}

void ContainerCharacteristicsExecutor::setTimeStep(units::Time time) {
    timeSlice = time;
}

units::Time ContainerCharacteristicsExecutor::timeStep() {
    const MachineFlowStringAdapter::FlowsVector & flowsVector = machineFlow.updateFlows();

    return timeSlice;
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
