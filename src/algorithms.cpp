#include "algorithms.hpp"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <functional>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

namespace {
using Clock = std::chrono::high_resolution_clock;

bool graphContains(const Graph &graph, const std::string &node) {
  return graph.find(node) != graph.end();
}

int levelRank(const std::string &level) {
  if (level == "Pemula")
    return 1;
  if (level == "Menengah")
    return 2;
  if (level == "Lanjutan")
    return 3;
  return 4;
}

bool comesBefore(const Resource &left, const Resource &right,
                 const std::string &field, bool descending) {
  bool less = false;
  if (field == "name") {
    less = toLower(left.name) < toLower(right.name);
  } else if (field == "rating") {
    less = left.rating < right.rating;
  } else if (field == "duration") {
    less = left.durationHours < right.durationHours;
  } else if (field == "level") {
    less = levelRank(left.level) < levelRank(right.level);
  } else {
    less = left.id < right.id;
  }

  if (descending) {
    if (field == "name")
      return toLower(left.name) > toLower(right.name);
    if (field == "rating")
      return left.rating > right.rating;
    if (field == "duration")
      return left.durationHours > right.durationHours;
    if (field == "level")
      return levelRank(left.level) > levelRank(right.level);
    return left.id > right.id;
  }
  return less;
}

std::vector<Resource> mergeSortRecursive(const std::vector<Resource> &data,
                                         const std::string &field,
                                         bool descending,
                                         std::size_t &comparisons,
                                         std::size_t &moves) {
  if (data.size() <= 1) {
    return data;
  }

  const std::size_t middle = data.size() / 2;
  std::vector<Resource> left(data.begin(),
                             data.begin() + static_cast<long>(middle));
  std::vector<Resource> right(data.begin() + static_cast<long>(middle),
                              data.end());

  left = mergeSortRecursive(left, field, descending, comparisons, moves);
  right = mergeSortRecursive(right, field, descending, comparisons, moves);

  std::vector<Resource> merged;
  merged.reserve(data.size());
  std::size_t i = 0;
  std::size_t j = 0;

  while (i < left.size() && j < right.size()) {
    ++comparisons;
    if (comesBefore(left[i], right[j], field, descending)) {
      merged.push_back(left[i++]);
    } else {
      merged.push_back(right[j++]);
    }
    ++moves;
  }

  while (i < left.size()) {
    merged.push_back(left[i++]);
    ++moves;
  }
  while (j < right.size()) {
    merged.push_back(right[j++]);
    ++moves;
  }

  return merged;
}
} // namespace

std::string toLower(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](unsigned char character) {
                   return static_cast<char>(std::tolower(character));
                 });
  return value;
}

std::vector<std::string> bfsTraversal(const Graph &graph,
                                      const std::string &start) {
  if (!graphContains(graph, start))
    return {};

  std::queue<std::string> nodes;
  std::unordered_set<std::string> visited;
  std::vector<std::string> order;

  nodes.push(start);
  visited.insert(start);

  while (!nodes.empty()) {
    const std::string current = nodes.front();
    nodes.pop();
    order.push_back(current);

    const auto graphEntry = graph.find(current);
    if (graphEntry == graph.end())
      continue;

    for (const std::string &neighbor : graphEntry->second) {
      if (visited.insert(neighbor).second) {
        nodes.push(neighbor);
      }
    }
  }
  return order;
}

std::vector<std::string> bfsShortestPath(const Graph &graph,
                                         const std::string &start,
                                         const std::string &target) {
  if (!graphContains(graph, start) || !graphContains(graph, target))
    return {};
  if (start == target)
    return {start};

  std::queue<std::string> nodes;
  std::unordered_set<std::string> visited;
  std::unordered_map<std::string, std::string> parent;

  nodes.push(start);
  visited.insert(start);

  bool found = false;
  while (!nodes.empty() && !found) {
    const std::string current = nodes.front();
    nodes.pop();

    for (const std::string &neighbor : graph.at(current)) {
      if (visited.insert(neighbor).second) {
        parent[neighbor] = current;
        if (neighbor == target) {
          found = true;
          break;
        }
        nodes.push(neighbor);
      }
    }
  }

  if (!found)
    return {};

  std::vector<std::string> path;
  for (std::string current = target;; current = parent[current]) {
    path.push_back(current);
    if (current == start)
      break;
  }
  std::reverse(path.begin(), path.end());
  return path;
}

std::vector<std::string> dfsTraversal(const Graph &graph,
                                      const std::string &start) {
  if (!graphContains(graph, start))
    return {};

  std::stack<std::string> nodes;
  std::unordered_set<std::string> visited;
  std::vector<std::string> order;
  nodes.push(start);

  while (!nodes.empty()) {
    const std::string current = nodes.top();
    nodes.pop();

    if (!visited.insert(current).second)
      continue;
    order.push_back(current);

    const auto &neighbors = graph.at(current);
    for (auto iterator = neighbors.rbegin(); iterator != neighbors.rend();
         ++iterator) {
      if (visited.find(*iterator) == visited.end()) {
        nodes.push(*iterator);
      }
    }
  }
  return order;
}

std::vector<std::string> dfsPath(const Graph &graph, const std::string &start,
                                 const std::string &target) {
  if (!graphContains(graph, start) || !graphContains(graph, target))
    return {};

  using PathState = std::pair<std::string, std::vector<std::string>>;
  std::stack<PathState> states;
  std::unordered_set<std::string> visited;
  states.push({start, {start}});

  while (!states.empty()) {
    PathState state = states.top();
    states.pop();

    const std::string &current = state.first;
    if (current == target)
      return state.second;
    if (!visited.insert(current).second)
      continue;

    const auto &neighbors = graph.at(current);
    for (auto iterator = neighbors.rbegin(); iterator != neighbors.rend();
         ++iterator) {
      if (visited.find(*iterator) == visited.end()) {
        std::vector<std::string> nextPath = state.second;
        nextPath.push_back(*iterator);
        states.push({*iterator, nextPath});
      }
    }
  }
  return {};
}

SearchResult linearSearch(const std::vector<Resource> &resources,
                          const std::string &query) {
  const auto startedAt = Clock::now();
  SearchResult result;
  const std::string normalizedQuery = toLower(query);

  for (const Resource &resource : resources) {
    ++result.comparisons;
    const std::string searchable =
        toLower(resource.name + " " + resource.category + " " + resource.level +
                " " + resource.type);
    if (searchable.find(normalizedQuery) != std::string::npos) {
      result.resources.push_back(resource);
    }
  }

  result.elapsedMilliseconds =
      std::chrono::duration<double, std::milli>(Clock::now() - startedAt)
          .count();
  return result;
}

BinarySearchResult
binarySearchExact(const std::vector<Resource> &sortedResources,
                  const std::string &exactName) {
  const auto startedAt = Clock::now();
  BinarySearchResult result;
  int left = 0;
  int right = static_cast<int>(sortedResources.size()) - 1;
  const std::string target = toLower(exactName);

  while (left <= right) {
    const int middle = left + (right - left) / 2;
    const std::string currentName = toLower(sortedResources[middle].name);
    ++result.comparisons;

    if (currentName == target) {
      result.found = true;
      result.resource = sortedResources[middle];
      break;
    }
    if (currentName < target) {
      left = middle + 1;
    } else {
      right = middle - 1;
    }
  }

  result.elapsedMilliseconds =
      std::chrono::duration<double, std::milli>(Clock::now() - startedAt)
          .count();
  return result;
}

SortResult bubbleSort(const std::vector<Resource> &resources,
                      const std::string &field, bool descending) {
  const auto startedAt = Clock::now();
  SortResult result;
  result.resources = resources;

  for (std::size_t i = 0; i < result.resources.size(); ++i) {
    bool swapped = false;
    for (std::size_t j = 0; j + 1 < result.resources.size() - i; ++j) {
      ++result.comparisons;
      if (comesBefore(result.resources[j + 1], result.resources[j], field,
                      descending)) {
        std::swap(result.resources[j], result.resources[j + 1]);
        ++result.swapsOrMoves;
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }

  result.elapsedMilliseconds =
      std::chrono::duration<double, std::milli>(Clock::now() - startedAt)
          .count();
  return result;
}

SortResult mergeSort(const std::vector<Resource> &resources,
                     const std::string &field, bool descending) {
  const auto startedAt = Clock::now();
  SortResult result;
  result.resources = mergeSortRecursive(
      resources, field, descending, result.comparisons, result.swapsOrMoves);
  result.elapsedMilliseconds =
      std::chrono::duration<double, std::milli>(Clock::now() - startedAt)
          .count();
  return result;
}
