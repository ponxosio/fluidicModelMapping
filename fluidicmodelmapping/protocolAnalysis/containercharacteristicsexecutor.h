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
    inline virtual void stopApplyLigth(const std::string & sourceId) {}

    virtual void applyTemperature(const std::string & sourceId, units::Temperature temperature);
    inline virtual void stopApplyTemperature(const std::string & sourceId){}

    virtual void stir(const std::string & idSource, units::Frequency intensity);
    inline virtual void stopStir(const std::string & idSource){}

    virtual void centrifugate(const std::string & idSource, units::Frequency intensity);
    virtual void stopCentrifugate(const std::string & idSource) = 0;

    virtual void shake(const std::string & idSource, units::Frequency intensity) = 0;
    virtual void stopShake(const std::string & idSource) = 0;

    virtual void startElectrophoresis(const std::string & idSource, units::ElectricField fieldStrenght) = 0;
    virtual ElectrophoresisResult stopElectrophoresis(const std::string & idSource) = 0;

    virtual units::Volume getVirtualVolume(const std::string & sourceId) = 0;
    virtual void loadContainer(const std::string & sourceId, units::Volume initialVolume) = 0;

    virtual void startMeasureOD(const std::string & sourceId, units::Frequency measurementFrequency, units::Length wavelength) = 0;
    virtual double getMeasureOD(const std::string & sourceId) = 0;

    virtual void startMeasureTemperature(const std::string & sourceId, units::Frequency measurementFrequency) = 0;
    virtual units::Temperature getMeasureTemperature(const std::string & sourceId) = 0;

    virtual void startMeasureLuminiscense(const std::string & sourceId, units::Frequency measurementFrequency) = 0;
    virtual units::LuminousIntensity getMeasureLuminiscense(const std::string & sourceId) = 0;

    virtual void startMeasureVolume(const std::string & sourceId, units::Frequency measurementFrequency) = 0;
    virtual units::Volume getMeasureVolume(const std::string & sourceId) = 0;

    virtual void startMeasureFluorescence(const std::string & sourceId,
                                          units::Frequency measurementFrequency,
                                          units::Length excitation,
                                          units::Length emission) = 0;
    virtual units::LuminousIntensity getMeasureFluorescence(const std::string & sourceId) = 0;

    virtual void setContinuosFlow(const std::string & idSource, const std::string & idTarget, units::Volumetric_Flow rate) = 0;
    virtual void stopContinuosFlow(const std::string & idSource, const std::string & idTarget) = 0;

    virtual units::Time transfer(const std::string & idSource, const std::string & idTarget, units::Volume volume) = 0;
    virtual void stopTransfer(const std::string & idSource, const std::string & idTarget) = 0;

    virtual units::Time mix(const std::string & idSource1,
                            const std::string & idSource2,
                            const std::string & idTarget,
                            units::Volume volume1,
                            units::Volume volume2) = 0;

    virtual void stopMix(const std::string & idSource1,
                         const std::string & idSource2,
                         const std::string & idTarget) = 0;

    virtual void setTimeStep(units::Time time) = 0;
    virtual units::Time timeStep() = 0;

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
