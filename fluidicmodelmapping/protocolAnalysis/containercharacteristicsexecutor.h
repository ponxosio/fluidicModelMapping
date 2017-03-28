#ifndef CONTAINERCHARACTERISTICSEXECUTOR_H
#define CONTAINERCHARACTERISTICSEXECUTOR_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <protocolGraph/execution_interface/actuatorsexecutioninterface.h>

#include "fluidicmodelmapping/heuristic/containercharacteristics.h"
#include "fluidicmodelmapping/protocolAnalysis/machineflowstringadapter.h"

class ContainerCharacteristicsExecutor : public ActuatorsExecutionInterface
{
public:
    ContainerCharacteristicsExecutor();
    virtual ~ContainerCharacteristicsExecutor();

    virtual void applyLigth(const std::string & sourceId, units::Length wavelength, units::LuminousIntensity intensity);
    virtual void applyTemperature(const std::string & sourceId, units::Temperature temperature);
    virtual void stir(const std::string & idSource, units::Frequency intensity);

    virtual units::Volume getVirtualVolume(const std::string & sourceId);
    virtual void loadContainer(const std::string & sourceId, units::Volume initialVolume);

    virtual double measureOD(const std::string & sourceId, units::Time duration, units::Frequency measurementFrequency, units::Length wavelength);
    virtual units::Temperature measureTemperature(const std::string & sourceId, units::Time duration, units::Frequency measurementFrequency);
    virtual units::LuminousIntensity measureLuminiscense(const std::string & sourceId, units::Time duration, units::Frequency measurementFrequency);
    virtual units::Volume measureVolume(const std::string & sourceId, units::Time duration, units::Frequency measurementFrequency);
    virtual units::LuminousIntensity measureFluorescence(const std::string & sourceId, units::Time duration, units::Frequency measurementFrequency);

    virtual void mix(const std::string & idSource1,
                     const std::string & idSource2,
                     const std::string & idTarget,
                     units::Volume volume1,
                     units::Volume volume2);
    virtual void setContinuosFlow(const std::string & idSource, const std::string & idTarget, units::Volumetric_Flow rate);
    virtual void stopContinuosFlow(const std::string & idSource, const std::string & idTarget);
    virtual void transfer(const std::string & idSource, const std::string & idTarget, units::Volume volume);

    virtual void setTimeStep(units::Time time);
    virtual units::Time timeStep();

    inline const std::unordered_map<std::string,ContainerCharacteristics> & getVcCharacteristicsMap() const {
        return vcCharacteristicsMap;
    }
    inline const std::vector<MachineFlowStringAdapter::FlowsVector> & getFlowsInTime() const {
        return flowsInTime;
    }
protected:
    units::Time timeSlice;
    MachineFlowStringAdapter machineFlow;
    std::unordered_map<std::string,ContainerCharacteristics> vcCharacteristicsMap;
    std::vector<MachineFlowStringAdapter::FlowsVector> flowsInTime;

    ContainerCharacteristics & getContainerCharacteristics(const std::string & sourceId);
};

#endif // CONTAINERCHARACTERISTICSEXECUTOR_H
