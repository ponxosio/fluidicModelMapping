#ifndef CONTAINERCHARACTERISTICSEXECUTOR_H
#define CONTAINERCHARACTERISTICSEXECUTOR_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <protocolGraph/execution_interface/actuatorssimulationinterface.h>

#include <graph/Edge.h>
#include <graph/Graph.h>
#include <graph/Node.h>

#include <utils/memento.h>
#include <utils/machineflowstringadapter.h>

#include "fluidicmodelmapping/heuristic/containercharacteristics.h"
#include "fluidicmodelmapping/protocolAnalysis/workingrangemanager.h"

class ContainerCharacteristicsExecutor : public ActuatorsSimulationInterface
{
public:
    ContainerCharacteristicsExecutor(units::Volumetric_Flow defaultRate);
    virtual ~ContainerCharacteristicsExecutor();

    virtual void applyLigth(const std::string & sourceId,
                            std::shared_ptr<MathematicOperable> wavelength,
                            units::Length wavelengthUnits,
                            std::shared_ptr<MathematicOperable> intensity,
                            units::LuminousIntensity intensityUnits);
    inline virtual void stopApplyLigth(const std::string & sourceId) {}

    virtual void applyTemperature(const std::string & sourceId,
                                  std::shared_ptr<MathematicOperable> temperature,
                                  units::Temperature temperatureUnits);
    inline virtual void stopApplyTemperature(const std::string & sourceId){}

    virtual void stir(const std::string & idSource,
                      std::shared_ptr<MathematicOperable> intensity,
                      units::Frequency intensityUnits);
    inline virtual void stopStir(const std::string & idSource){}

    virtual void centrifugate(const std::string & idSource,
                              std::shared_ptr<MathematicOperable> intensity,
                              units::Frequency intensityUnits);
    inline virtual void stopCentrifugate(const std::string & idSource){}

    virtual void shake(const std::string & idSource,
                       std::shared_ptr<MathematicOperable> intensity,
                       units::Frequency intensityUnits);
    inline virtual void stopShake(const std::string & idSource){}

    virtual void startElectrophoresis(const std::string & idSource,
                                      std::shared_ptr<MathematicOperable> fieldStrenght,
                                      units::ElectricField fieldStrenghtUnits);

    inline virtual std::shared_ptr<ElectrophoresisResult> stopElectrophoresis(const std::string & idSource) {
        return NULL;
    }

    virtual units::Volume getVirtualVolume(const std::string & sourceId);
    virtual void loadContainer(const std::string & sourceId, units::Volume initialVolume);

    virtual void startMeasureOD(const std::string & sourceId,
                                std::shared_ptr<MathematicOperable> measurementFrequency,
                                units::Frequency measurementFrequencyUnits,
                                std::shared_ptr<MathematicOperable> wavelength,
                                units::Length wavelengthUnits);
    inline virtual double getMeasureOD(const std::string & sourceId) {
        return 0;
    }

    virtual void startMeasureTemperature(const std::string & sourceId,
                                         std::shared_ptr<MathematicOperable> measurementFrequency,
                                         units::Frequency measurementFrequencyUnits);

    inline virtual units::Temperature getMeasureTemperature(const std::string & sourceId) {
        return (0 * units::C);
    }

    virtual void startMeasureLuminiscense(const std::string & sourceId,
                                          std::shared_ptr<MathematicOperable> measurementFrequency,
                                          units::Frequency measurementFrequencyUnits);

    inline virtual units::LuminousIntensity getMeasureLuminiscense(const std::string & sourceId) {
        return (0 * units::cd);
    }

    virtual void startMeasureVolume(const std::string & sourceId,
                                    std::shared_ptr<MathematicOperable> measurementFrequency,
                                    units::Frequency measurementFrequencyUnits);

    inline virtual units::Volume getMeasureVolume(const std::string & sourceId) {
        return (0 * units::l);
    }

    virtual void startMeasureFluorescence(const std::string & sourceId,
                                          std::shared_ptr<MathematicOperable> measurementFrequency,
                                          units::Frequency measurementFrequencyUnits,
                                          std::shared_ptr<MathematicOperable> excitation,
                                          units::Length excitationUnits,
                                          std::shared_ptr<MathematicOperable> emission,
                                          units::Length emissionUnits);

    inline virtual units::LuminousIntensity getMeasureFluorescence(const std::string & sourceId) {
        return (0 * units::cd);
    }

    virtual void setContinuosFlow(const std::string & idSource,
                                  const std::string & idTarget,
                                  std::shared_ptr<MathematicOperable> rate,
                                  units::Volumetric_Flow rateUnits);
    virtual void stopContinuosFlow(const std::string & idSource, const std::string & idTarget);

    virtual units::Time transfer(const std::string & idSource,
                                 const std::string & idTarget,
                                 std::shared_ptr<MathematicOperable> volume,
                                 units::Volume volumeUnits);
    virtual void stopTransfer(const std::string & idSource, const std::string & idTarget);

    virtual units::Time mix(const std::string & idSource1,
                            const std::string & idSource2,
                            const std::string & idTarget,
                            std::shared_ptr<MathematicOperable> volume1,
                            units::Volume volume1Units,
                            std::shared_ptr<MathematicOperable> volume2,
                            units::Volume volume2Units);

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
    inline const std::unordered_map<std::string, WorkingRangeManager> & getVcWorkingrangeMap() const {
        return vcWorkingrangeMap;
    }
    inline const Graph<Node, Edge> & getConnectionGraph() const {
        return connectionGraph;
    }
    inline std::shared_ptr<MachineFlowStringAdapter> getMachineFlows() const {
        return machineFlow;
    }

protected:
    units::Volumetric_Flow defaultRate;

    units::Time timeSlice;
    std::shared_ptr<MachineFlowStringAdapter> machineFlow;

    Graph<Node, Edge> connectionGraph;

    std::unordered_map<std::string, ContainerCharacteristics> vcCharacteristicsMap;
    std::unordered_map<std::string, WorkingRangeManager> vcWorkingrangeMap;

    bool flowsNeedChecking;
    std::vector<MachineFlowStringAdapter::FlowsVector> flowsInTime;

    void analyzeFlowInTime(const MachineFlowStringAdapter::FlowsVector & flows) throw(std::invalid_argument);
    void addFlowsInTime(const MachineFlowStringAdapter::FlowsVector & flows) throw(std::invalid_argument);

    ContainerCharacteristics & getContainerCharacteristics(const std::string & sourceId);
    WorkingRangeManager & getContainerWorkingRange(const std::string & sourceId);
};

#endif // CONTAINERCHARACTERISTICSEXECUTOR_H
