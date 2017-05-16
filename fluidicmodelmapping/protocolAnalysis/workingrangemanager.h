#ifndef WORKINGRANGEMANAGER_H
#define WORKINGRANGEMANAGER_H

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

class WorkingRangeManager
{
public:
    typedef std::unordered_map<Function::OperationType, std::shared_ptr<ComparableRangeInterface>, Function::OperationTypeHash> WorkingRangeMap;

    WorkingRangeManager();
    virtual ~WorkingRangeManager();

    /*
        route,
        pump,
        heat,
        apply_light,
        measure_od,
        stir,
        centrifugate,
        shake,
        electrophoresis,
        measure_temperature,
        measure_luminiscence,
        measure_fluorescence,
        measure_volume
    */



    inline const WorkingRangeMap & getWorkingRangeMap() const {
        return workingRangeMap;
    }
protected:
    WorkingRangeMap workingRangeMap;
};

#endif // WORKINGRANGEMANAGER_H
