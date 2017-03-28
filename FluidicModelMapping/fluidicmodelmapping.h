#ifndef FLUIDICMODELMAPPING_H
#define FLUIDICMODELMAPPING_H

#include <memory>

#include <commonmodel/mappinginterface/mappinginterface.h>
#include <protocolGraph/ProtocolGraph.h>

class FluidicModelMapping : public MappingInterface
{
public:
    FluidicModelMapping();

    virtual bool areCompatible(std::shared_ptr<ProtocolGraph> graph);
    virtual int getMappedComponent(const string &virtualContainer);

protected:
};

#endif // FLUIDICMODELMAPPING_H
