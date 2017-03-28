#ifndef CONTAINERCHARACTERISTICS_H
#define CONTAINERCHARACTERISTICS_H

#include <bitset>
#include <string>
#include <vector>

#include <commonmodel/functions/functionset.h>
#include <fluidicmachinemodel/fluidicnode/containernode.h>

class ContainerCharacteristics
{
public:
    typedef std::vector<std::vector<std::string>> ConnectionVector;

    ContainerCharacteristics();
    ContainerCharacteristics(const std::string & virtualContainerName);
    virtual ~ContainerCharacteristics();

    void addMustConnectVector(const std::vector<std::string> & container2connect);

    inline void setType(ContainerNode::ContainerType type) {
        this->type = type;
    }
    inline void addFunctions(unsigned long mask) {
        this->neccesaryFunctionsMask = neccesaryFunctionsMask | mask;
    }

    inline const std::string & getName() const {
        return containerName;
    }

    inline unsigned long getNeccesaryFunctionsMask() const {
        return neccesaryFunctionsMask;
    }

    inline ContainerNode::ContainerType getType() const {
        return type;
    }

    inline const ConnectionVector & getMustConnectVector() const {
        return mustConnectToVector;
    }

protected:
    std::string containerName;
    unsigned long neccesaryFunctionsMask;
    ContainerNode::ContainerType type;
    ConnectionVector mustConnectToVector;

    void copyConnectionVector(const ConnectionVector & connectionVector);
};

#endif // CONTAINERCHARACTERISTICS_H
