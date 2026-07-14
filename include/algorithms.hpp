#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "data.hpp"
#include "models.hpp"

#include <string>
#include <vector>

std::vector<std::string> bfsTraversal(const Graph& graph, const std::string& start);
std::vector<std::string> bfsShortestPath(
    const Graph& graph,
    const std::string& start,
    const std::string& target
);

std::vector<std::string> dfsTraversal(const Graph& graph, const std::string& start);
std::vector<std::string> dfsPath(
    const Graph& graph,
    const std::string& start,
    const std::string& target
);

SearchResult linearSearch(
    const std::vector<Resource>& resources,
    const std::string& query
);

BinarySearchResult binarySearchExact(
    const std::vector<Resource>& sortedResources,
    const std::string& exactName
);

SortResult bubbleSort(
    const std::vector<Resource>& resources,
    const std::string& field,
    bool descending
);

SortResult mergeSort(
    const std::vector<Resource>& resources,
    const std::string& field,
    bool descending
);

std::string toLower(std::string value);

#endif
