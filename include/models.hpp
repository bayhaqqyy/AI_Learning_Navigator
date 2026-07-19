#ifndef MODELS_HPP
#define MODELS_HPP

#include <string>
#include <vector>

struct Resource {
    int id{};
    std::string name;
    std::string category;
    std::string level;
    double rating{};
    int durationHours{};
    std::string type;
};

struct SearchResult {
    std::vector<Resource> resources;
    std::size_t comparisons{};
    double elapsedMilliseconds{};
};

struct BinarySearchResult {
    bool found{};
    Resource resource{};
    std::size_t comparisons{};
    double elapsedMilliseconds{};
};

struct SortResult {
    std::vector<Resource> resources;
    std::size_t comparisons{};
    std::size_t swapsOrMoves{};
    double elapsedMilliseconds{};
};

struct ComplexityInfo {
    std::string algorithm;
    std::string bestCase;
    std::string averageCase;
    std::string worstCase;
    std::string space;
};

#endif
