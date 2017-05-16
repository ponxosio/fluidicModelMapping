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
    inline virtual void stopCentrifugate(const std::string & idSource){}

    virtual void shake(const std::string & idSource, units::Frequency intensity);
    inline virtual void stopShake(const std::string & idSource){}

    virtual void startElectrophoresis(const std::string & idSource, units::ElectricField fieldStrenght);

    inline virtual std::shared_ptr<ElectrophoresisResult> stopElectrophoresis(const std::string & idSource) {
        return NULL;
    }

    virtual units::Volume getVirtualVolume(const std::string & sourceId);
    virtual void loadContainer(const std::string & sourceId, units::Volume initialVolume);

    virtual void startMeasureOD(const std::string & sourceId, units::Frequency measurementFrequency, units::Length wavelength);
    inline virtual double getMeasureOD(const std::string & sourceId) {
        return 0;
    }

    virtual void startMeasureTemperature(const std::string & sourceId, units::Frequency measurementFrequency);

    inline virtual units::Temperature getMeasureTemperature(const std::string & sourceId) {
        return (0 * units::K);
    }

    virtual void startMeasureLuminiscense(const std::string & sourceId, units::Frequency measurementFrequency);

    inline virtual units::LuminousIntensity getMeasureLuminiscense(const std::string & sourceId) {
        return (0 * units::cd);
    }

    virtual void startMeasureVolume(const std::string & sourceId, units::Frequency measurementFrequency);

    inline virtual units::Volume getMeasureVolume(const std::string & sourceId) {
        return (0 * units::l);
    }

    virtual void startMeasureFluorescence(const std::string & sourceId,
                                          units::Frequency measurementFrequency,
                                          units::Length excitation,
                                          units::Length emission);
    inline virtual units::LuminousIntensity getMeasureFluorescence(const std::string & sourceId) {
        return (0 * units::cd);
    }

    virtual void setContinuosFlow(const std::string & idSource, const std::string & idTarget, units::Volumetric_Flow rate);
    virtual void stopContinuosFlow(const std::string & idSource, const std::string & idTarget);

    virtual units::Time transfer(const std::string & idSource, const std::string & idTarget, units::Volume volume);
    virtual void stopTransfer(const std::string & idSource, const std::string & idTarget);

    virtual units::Time mix(const std::string & idSource1,
                            const std::string & idSource2,
                            const std::string & idTarget,
                            units::Volume volume1,
                            units::Volume volume2);

    virtual void stopMix(const std::string & idSource1,
                         const std::string & idSource2,
                         const std::string & idTarget);

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
    std::unordered_map<std::string, ContainerCharacteristics> vcCharacteristicsMap;

    std::vector<MachineFlowStringAdapter::FlowsVector> flowsInTime;

    ContainerCharacteristics & getContainerCharacteristics(const std::string & sourceId);
};

#endif // CONTAINERCHARACTERISTICSEXECUTOR_H
