#ifndef WORKINGRANGEMANAGER_H
#define WORKINGRANGEMANAGER_H

#include <limits>
#include <unordered_map>

#include <commonmodel/functions/function.h>
#include <commonmodel/functions/ranges/comparablerangeinterface.h>

#include <commonmodel/functions/ranges/centrifugationworkingrange.h>
#include <commonmodel/functions/ranges/electrophoresisworkingrange.h>
#include <commonmodel/functions/ranges/emptyworkingrange.h>
#include <commonmodel/functions/ranges/heaterworkingrange.h>
#include <commonmodel/functions/ranges/ligthworkingrange.h>
#include <commonmodel/functions/ranges/measurefluorescenceworkingrange.h>
#include <commonmodel/functions/ranges/measureodworkingrange.h>
#include <commonmodel/functions/ranges/pumpworkingrange.h>
#include <commonmodel/functions/ranges/shakeworkingrange.h>
#include <commonmodel/functions/ranges/stirworkingrange.h>

#include <utils/units.h>

class WorkingRangeManager
{
public:
    typedef std::unordered_map<Function::OperationType, std::shared_ptr<ComparableRangeInterface>, Function::OperationTypeHash> WorkingRangeMap;

    WorkingRangeManager();
    virtual ~WorkingRangeManager();

    void setValveWorkingRate();
    void setPumpWorkingRange(units::Volumetric_Flow rateValue);
    void setHeaterWorkingRange(units::Temperature temperatreValue);
    void setLigthWorkingRange(units::LuminousIntensity intensity, units::Length wavelength);
    void setOdSensorWorkingRange(units::Length wavelength);
    void setStirerWorkingRange(units::Frequency intensity);
    void setShakerWorkingRange(units::Frequency intensity);
    void setCentrifugerWorkingRange(units::Frequency intensity);
    void setElectrophorerWorkingRange(units::ElectricField intensity);
    void setTemperatureSensorWorkingRange();
    void setLuminiscenceSensorWorkingRange();
    void setFluorescenceSensorWorkingRange(units::Length emission, units::Length excitation);
    void setVolumeSensorWorkingRange();

    void setActuatorToInfinite(Function::OperationType op);

    inline const WorkingRangeMap & getWorkingRangeMap() const {
        return workingRangeMap;
    }
protected:
    WorkingRangeMap workingRangeMap;
};

#endif // WORKINGRANGEMANAGER_H
