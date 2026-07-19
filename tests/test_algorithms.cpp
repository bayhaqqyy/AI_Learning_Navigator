#include "algorithms.hpp"
#include "data.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

namespace {
void testBfsTraversal() {
    const Graph graph = createAiLearningGraph();
    const auto order = bfsTraversal(graph, "Mulai");
    assert(!order.empty());
    assert(order.front() == "Mulai");
    assert(order.size() == graph.size());
}

void testBfsShortestPath() {
    const Graph graph = createAiLearningGraph();
    const auto path = bfsShortestPath(graph, "Mulai", "Generative AI");
    assert(!path.empty());
    assert(path.front() == "Mulai");
    assert(path.back() == "Generative AI");
    assert(path.size() == 5);
}

void testDfsTraversal() {
    const Graph graph = createAiLearningGraph();
    const auto order = dfsTraversal(graph, "Mulai");
    assert(!order.empty());
    assert(order.front() == "Mulai");
    assert(order.size() == graph.size());
}

void testDfsPath() {
    const Graph graph = createAiLearningGraph();
    const auto path = dfsPath(graph, "Mulai", "Proyek AI");
    assert(!path.empty());
    assert(path.front() == "Mulai");
    assert(path.back() == "Proyek AI");
}

void testLinearSearch() {
    const auto resources = createAiResources();
    const SearchResult result = linearSearch(resources, "Generative");
    assert(result.resources.size() == 2);
    assert(result.comparisons == resources.size());
}

void testBinarySearch() {
    const auto resources = createAiResources();
    const SortResult sorted = mergeSort(resources, "name", false);
    const BinarySearchResult result = binarySearchExact(sorted.resources, "Deep Learning Dasar");
    assert(result.found);
    assert(result.resource.id == 8);
    assert(result.comparisons <= 5);
}

void testBubbleSort() {
    const auto resources = createAiResources();
    const SortResult result = bubbleSort(resources, "duration", false);
    assert(result.resources.front().durationHours == 4);
    assert(result.resources.back().durationHours == 24);
}

void testMergeSort() {
    const auto resources = createAiResources();
    const SortResult result = mergeSort(resources, "rating", true);
    assert(std::fabs(result.resources.front().rating - 4.9) < 0.0001);
    for (std::size_t i = 1; i < result.resources.size(); ++i) {
        assert(result.resources[i - 1].rating >= result.resources[i].rating);
    }
}
}  // namespace

int main() {
    testBfsTraversal();
    testBfsShortestPath();
    testDfsTraversal();
    testDfsPath();
    testLinearSearch();
    testBinarySearch();
    testBubbleSort();
    testMergeSort();

    std::cout << "[PASS] 8 pengujian algoritma berhasil.\n";
    return 0;
}