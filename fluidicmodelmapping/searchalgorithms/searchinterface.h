#ifndef SEARCHINTERFACE_H
#define SEARCHINTERFACE_H

#include <string>
#include <unordered_map>

class SearchInterface
{
public:
    typedef std::unordered_map<std::string, int> RelationTable;

    SearchInterface(){}
    virtual ~SearchInterface(){}

    virtual bool startSearch() = 0;

    inline virtual const std::vector<RelationTable> & getRelationTable() const {
        return relationsVector;
    }

protected:
    std::vector<RelationTable> relationsVector;

};

#endif // SEARCHINTERFACE_H
