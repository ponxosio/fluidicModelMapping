#ifndef CONTAINERCHARACTERISTICS_H
#define CONTAINERCHARACTERISTICS_H

#include <bitset>
#include <string>
#include <vector>
#include <unordered_map>

#include <commonmodel/functions/functionset.h>
#include <commonmodel/functions/function.h>
#include <commonmodel/functions/ranges/comparablerangeinterface.h>

#include <fluidicmachinemodel/fluidicnode/containernode.h>

#include "fluidicmodelmapping/fluidicmodelmapping_global.h"

class CONTAINERCHARACTERISTICS_EXPORT ContainerCharacteristics
{
public:

    typedef std::bitset<Function::MAX_OPTYPE> FunctionsBitSet;
    typedef std::unordered_map<Function::OperationType, const std::shared_ptr<const ComparableRangeInterface>, Function::OperationTypeHash> WorkingRangeMap;

    typedef struct _ContainerCharacteristicsComparator {
        bool operator()(const ContainerCharacteristics & x, const ContainerCharacteristics & y) const throw () {
            int opsX = x.neccesaryFunctionsMask.count();
            int opsY = y.neccesaryFunctionsMask.count();
            if ( opsX == opsY) {
                return (x.numberConnections) > (y.numberConnections);
            } else {
                return opsX > opsY;
            }
        }
    } ContainerCharacteristicsComparator;

    ContainerCharacteristics();
    ContainerCharacteristics(const ContainerCharacteristics & cc);
    ContainerCharacteristics(const std::string & virtualContainerName);
    virtual ~ContainerCharacteristics();

    bool compatible(const ContainerCharacteristics & containerChar) const;
    void addFunctions(Function::OperationType op);
    void addFunctions(const FunctionsBitSet & functions);

    void addWorkingRange(Function::OperationType op, const std::shared_ptr<const ComparableRangeInterface> workingRange) throw(std::invalid_argument);

    inline void setType(ContainerNode::ContainerType type) {
        this->type = type;
    }

    inline void setNumberConnections(unsigned int numberConnections) {
        this->numberConnections = numberConnections;
    }

    inline const std::string & getName() const {
        return containerName;
    }

    inline const FunctionsBitSet & getNeccesaryFunctionsMask() const {
        return neccesaryFunctionsMask;
    }

    inline ContainerNode::ContainerType getType() const {
        return type;
    }

    inline unsigned int getNumberConnections() const {
        return numberConnections;
    }

    inline const WorkingRangeMap & getWorkingRangeMap() const {
        return workingRangeMap;
    }

    inline units::Volume getMinCapacity() const {
        return minCapacity;
    }

    inline void setMinCapacity(units::Volume minCapacity) {
        this->minCapacity = minCapacity;
    }


protected:
    std::string containerName;

    unsigned int numberConnections;

    FunctionsBitSet neccesaryFunctionsMask;
    ContainerNode::ContainerType type;
    WorkingRangeMap workingRangeMap;

    units::Volume minCapacity;

    bool areWorkingRangeMapsCompatible(const WorkingRangeMap & othermap) const;
};

#endif // CONTAINERCHARACTERISTICS_H
