#ifndef SEARCHINTERFACE_H
#define SEARCHINTERFACE_H

#include <string>
#include <sstream>
#include <unordered_map>

class SearchInterface
{
public:
    typedef std::unordered_map<std::string, int> RelationTable;

    inline static std::string relationTableToString(const RelationTable & table) {
        std::stringstream stream;
        stream << "[";
        for(const auto & pair : table) {
            stream << "(" << pair.first << ":" << pair.second << "),";
        }
        stream << "]";
    }

    SearchInterface(){}
    virtual ~SearchInterface(){}

    virtual bool startSearch(std::string & errorMsg) = 0;

    inline virtual const std::vector<RelationTable> & getRelationTable() const {
        return relationsVector;
    }

protected:
    std::vector<RelationTable> relationsVector;

};

#endif // SEARCHINTERFACE_H
