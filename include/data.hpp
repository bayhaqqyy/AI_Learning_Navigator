#ifndef DATA_HPP
#define DATA_HPP

#include "models.hpp"

#include <map>
#include <string>
#include <vector>

using Graph = std::map<std::string, std::vector<std::string>>;

Graph createAiLearningGraph();
std::vector<Resource> createAiResources();
std::vector<ComplexityInfo> createComplexityTable();
std::vector<std::string> getAllTopics(const Graph& graph);

#endif
