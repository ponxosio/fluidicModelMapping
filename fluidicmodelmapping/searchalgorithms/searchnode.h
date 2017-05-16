#ifndef SEARCHNODE_H
#define SEARCHNODE_H

#include <memory>
#include <vector>

class HeuristicInterface;

class SearchNode
{
public:
    typedef struct SearchNodeCompareFunct_ {
        bool operator()(const SearchNode & x, const SearchNode & y) const throw () {
            return x.heuristicValue > y.heuristicValue;
        }
    } SearchNodeCompareFunct;


    SearchNode(int lastMappedContainer, const std::vector<int> & mappedContainers, std::shared_ptr<HeuristicInterface> heuristic);
    SearchNode(const SearchNode & node);
    virtual ~SearchNode();

    inline bool isSolutionCandidate() const {
        return (lastMappedContainer == mappedContainers.size()-1);
    }
    inline double getHeuristicValue() const {
        return heuristicValue;
    }
    inline int getLastMappedContainer() const {
        return lastMappedContainer;
    }
    inline const std::vector<int> & getMappedContainers() const {
        return mappedContainers;
    }
    inline const std::vector<int> & getCompatibleNextContainer() const {
        return compatibleNodesNextContainer;
    }

protected:
    int lastMappedContainer;
    double heuristicValue;
    std::vector<int> mappedContainers;
    std::vector<int> compatibleNodesNextContainer;

};

#endif // SEARCHNODE_H
