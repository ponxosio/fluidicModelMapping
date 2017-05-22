#include "containercharacteristicsexecutor.h"

ContainerCharacteristicsExecutor::ContainerCharacteristicsExecutor(
        units::Volumetric_Flow defaultRate,
        units::Volume defaultVolume)
{
    this->defaultRate = defaultRate;
    this->defaultVolume = defaultVolume;
    this->flowsNeedChecking = false;
}

ContainerCharacteristicsExecutor::~ContainerCharacteristicsExecutor() {

}

void ContainerCharacteristicsExecutor::applyLigth(
        const std::string & sourceId,
        std::shared_ptr<MathematicOperable> wavelength,
        units::Length wavelengthUnits,
        std::shared_ptr<MathematicOperable> intensity,
        units::LuminousIntensity intensityUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);    
    cCh.addFunctions(Function::apply_light);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    if (wavelength->isPhysical() || intensity->isPhysical()) {
        workingRange.setActuatorToInfinite(Function::apply_light);
    } else {
        workingRange.setLigthWorkingRange(intensity->getValue() * intensityUnits, wavelength->getValue() * wavelengthUnits);
    }
}

void ContainerCharacteristicsExecutor::applyTemperature(
        const std::string & sourceId,
        std::shared_ptr<MathematicOperable> temperature,
        units::Temperature temperatureUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    cCh.addFunctions(Function::heat);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    if (temperature->isPhysical()) {
        workingRange.setActuatorToInfinite(Function::heat);
    } else {
        workingRange.setHeaterWorkingRange(temperature->getValue() * temperatureUnits);
    }
}

void ContainerCharacteristicsExecutor::stir(
        const std::string & idSource,
        std::shared_ptr<MathematicOperable> intensity,
        units::Frequency intensityUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(idSource);
    cCh.addFunctions(Function::stir);

    WorkingRangeManager & workingRange = getContainerWorkingRange(idSource);
    if (intensity->isPhysical()) {
        workingRange.setActuatorToInfinite(Function::stir);
    } else {
        workingRange.setStirerWorkingRange(intensity->getValue() * intensityUnits);
    }
}

void ContainerCharacteristicsExecutor::centrifugate(
        const std::string & idSource,
        std::shared_ptr<MathematicOperable> intensity,
        units::Frequency intensityUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(idSource);
    cCh.addFunctions(Function::centrifugate);

    WorkingRangeManager & workingRange = getContainerWorkingRange(idSource);
    if (intensity->isPhysical()) {
        workingRange.setActuatorToInfinite(Function::centrifugate);
    } else {
        workingRange.setCentrifugerWorkingRange(intensity->getValue() * intensityUnits);
    }
}

void ContainerCharacteristicsExecutor::shake(
        const std::string & idSource,
        std::shared_ptr<MathematicOperable> intensity,
        units::Frequency intensityUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(idSource);
    cCh.addFunctions(Function::shake);

    WorkingRangeManager & workingRange = getContainerWorkingRange(idSource);
    if (intensity->isPhysical()) {
        workingRange.setActuatorToInfinite(Function::shake);
    } else {
        workingRange.setShakerWorkingRange(intensity->getValue() * intensityUnits);
    }
}

void ContainerCharacteristicsExecutor::startElectrophoresis(
        const std::string & idSource,
        std::shared_ptr<MathematicOperable> fieldStrenght,
        units::ElectricField fieldStrenghtUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(idSource);
    cCh.addFunctions(Function::electrophoresis);

    WorkingRangeManager & workingRange = getContainerWorkingRange(idSource);
    if (fieldStrenght->isPhysical()) {
        workingRange.setActuatorToInfinite(Function::electrophoresis);
    } else {
        workingRange.setElectrophorerWorkingRange(fieldStrenght->getValue() * fieldStrenghtUnits);
    }
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
        std::shared_ptr<MathematicOperable> measurementFrequency,
        units::Frequency measurementFrequencyUnits,
        std::shared_ptr<MathematicOperable> wavelength,
        units::Length wavelengthUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    cCh.addFunctions(Function::measure_od);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    if (wavelength->isPhysical()) {
        workingRange.setActuatorToInfinite(Function::measure_od);
    } else {
        workingRange.setOdSensorWorkingRange(wavelength->getValue() * wavelengthUnits);
    }
}

void ContainerCharacteristicsExecutor::startMeasureTemperature(
        const std::string & sourceId,
        std::shared_ptr<MathematicOperable> measurementFrequency,
        units::Frequency measurementFrequencyUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    cCh.addFunctions(Function::measure_temperature);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    workingRange.setTemperatureSensorWorkingRange();
}

void ContainerCharacteristicsExecutor::startMeasureLuminiscense(
        const std::string & sourceId,
        std::shared_ptr<MathematicOperable> measurementFrequency,
        units::Frequency measurementFrequencyUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    cCh.addFunctions(Function::measure_luminiscence);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    workingRange.setLuminiscenceSensorWorkingRange();
}

void ContainerCharacteristicsExecutor::startMeasureVolume(
        const std::string & sourceId,
        std::shared_ptr<MathematicOperable> measurementFrequency,
        units::Frequency measurementFrequencyUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    cCh.addFunctions(Function::measure_volume);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    workingRange.setVolumeSensorWorkingRange();
}

void ContainerCharacteristicsExecutor::startMeasureFluorescence(
        const std::string & sourceId,
        std::shared_ptr<MathematicOperable> measurementFrequency,
        units::Frequency measurementFrequencyUnits,
        std::shared_ptr<MathematicOperable> excitation,
        units::Length excitationUnits,
        std::shared_ptr<MathematicOperable> emission,
        units::Length emissionUnits)
{
    ContainerCharacteristics & cCh = getContainerCharacteristics(sourceId);
    cCh.addFunctions(Function::measure_fluorescence);

    WorkingRangeManager & workingRange = getContainerWorkingRange(sourceId);
    if (excitation->isPhysical() || emission->isPhysical()) {
        workingRange.setActuatorToInfinite(Function::measure_fluorescence);
    } else {
        workingRange.setFluorescenceSensorWorkingRange(emission->getValue() * emissionUnits, excitation->getValue() * excitationUnits);
    }
}

void ContainerCharacteristicsExecutor::setContinuosFlow(
        const std::string & idSource,
        const std::string & idTarget,
        std::shared_ptr<MathematicOperable> rate,
        units::Volumetric_Flow rateUnits)
{
    flowsNeedChecking = true;

    if (!rate->isPhysical()) {
        machineFlow.addFlow(idSource, idTarget, rate->getValue() * rateUnits);
    } else {
        machineFlow.addFlow(idSource, idTarget, defaultRate);
    }
}

void ContainerCharacteristicsExecutor::stopContinuosFlow(const std::string & idSource, const std::string & idTarget) {
    flowsNeedChecking = true;
    machineFlow.removeFlow(idSource, idTarget);
}

units::Time ContainerCharacteristicsExecutor::transfer(
        const std::string & idSource,
        const std::string & idTarget,
        std::shared_ptr<MathematicOperable> volume,
        units::Volume volumeUnits)
{
    flowsNeedChecking = true;
    machineFlow.addFlow(idSource, idTarget, defaultRate);

    units::Time time2Transfer;
    if (!volume->isPhysical()) {
        time2Transfer = (volume->getValue() * volumeUnits) / defaultRate;
    } else {
        time2Transfer = defaultVolume/defaultRate;
    }
    return time2Transfer;
}

void ContainerCharacteristicsExecutor::stopTransfer(const std::string & idSource, const std::string & idTarget) {
    flowsNeedChecking = true;
    machineFlow.removeFlow(idSource, idTarget);
}

units::Time ContainerCharacteristicsExecutor::mix(
        const std::string & idSource1,
        const std::string & idSource2,
        const std::string & idTarget,
        std::shared_ptr<MathematicOperable> volume1,
        units::Volume volume1Units,
        std::shared_ptr<MathematicOperable> volume2,
        units::Volume volume2Units)
{
    units::Time duration1 = transfer(idSource1, idTarget, volume1, volume1Units);
    units::Time duration2 = transfer(idSource2, idTarget, volume2, volume2Units);
    return duration1 > duration2 ? duration1 : duration2;
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
    if (flowsNeedChecking) {
        const MachineFlowStringAdapter::FlowsVector & flowsVector = machineFlow.updateFlows();
        if (!flowsVector.empty()) {
            analyzeFlowInTime(flowsVector);
            flowsInTime.push_back(flowsVector);
        }
        flowsNeedChecking = false;
    }
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

                lastId = actualId;
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
