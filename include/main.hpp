#include "algorithms.hpp"
#include "data.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace {
constexpr int kNameWidth = 38;

void printHeader() {
    std::cout << "\n============================================================\n";
    std::cout << "                  AI LEARNING NAVIGATOR C++                 \n";
    std::cout << " Rekomendasi Jalur Belajar Artificial Intelligence          \n";
    std::cout << "============================================================\n";
}

void printMenu() {
    std::cout << "\nMENU UTAMA\n";
    std::cout << " 1. Tampilkan graph jalur belajar AI\n";
    std::cout << " 2. Traversal Breadth First Search (BFS)\n";
    std::cout << " 3. Traversal Depth First Search (DFS)\n";
    std::cout << " 4. Cari jalur belajar terpendek dengan BFS\n";
    std::cout << " 5. Cari jalur eksplorasi dengan DFS\n";
    std::cout << " 6. Linear Search resource pembelajaran\n";
    std::cout << " 7. Binary Search nama resource\n";
    std::cout << " 8. Bubble Sort resource\n";
    std::cout << " 9. Merge Sort resource\n";
    std::cout << "10. Tampilkan tabel Big O\n";
    std::cout << " 0. Keluar\n";
    std::cout << "------------------------------------------------------------\n";
}

int readInteger(const std::string& prompt, int minimum, int maximum) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        std::stringstream converter(input);
        int value = 0;
        char extra = '\0';
        if ((converter >> value) && !(converter >> extra) && value >= minimum && value <= maximum) {
            return value;
        }
        std::cout << "Input tidak valid. Masukkan angka " << minimum << " sampai " << maximum << ".\n";
    }
}

std::string readText(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

void printPath(const std::vector<std::string>& path) {
    if (path.empty()) {
        std::cout << "Jalur tidak ditemukan.\n";
        return;
    }
    for (std::size_t i = 0; i < path.size(); ++i) {
        if (i > 0) std::cout << " -> ";
        std::cout << path[i];
    }
    std::cout << "\nJumlah tahap: " << (path.size() - 1) << "\n";
}

void printTraversal(const std::vector<std::string>& order) {
    if (order.empty()) {
        std::cout << "Simpul awal tidak ditemukan.\n";
        return;
    }
    for (std::size_t i = 0; i < order.size(); ++i) {
        std::cout << std::setw(2) << (i + 1) << ". " << order[i] << "\n";
    }
    std::cout << "Total simpul dikunjungi: " << order.size() << "\n";
}

void printGraph(const Graph& graph) {
    std::cout << "\nREPRESENTASI GRAPH (ADJACENCY LIST)\n";
    std::cout << "------------------------------------------------------------\n";
    for (const auto& [node, neighbors] : graph) {
        std::cout << std::left << std::setw(29) << node << " : ";
        if (neighbors.empty()) {
            std::cout << "(tujuan akhir)";
        } else {
            for (std::size_t i = 0; i < neighbors.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << neighbors[i];
            }
        }
        std::cout << "\n";
    }
}

void printResourceTable(const std::vector<Resource>& resources, std::size_t maximumRows = 50) {
    if (resources.empty()) {
        std::cout << "Tidak ada resource yang ditemukan.\n";
        return;
    }

    std::cout << std::left
              << std::setw(4) << "ID"
              << std::setw(kNameWidth) << "Nama"
              << std::setw(12) << "Level"
              << std::setw(8) << "Rating"
              << std::setw(10) << "Durasi"
              << "Tipe\n";
    std::cout << std::string(86, '-') << "\n";

    const std::size_t rows = std::min(maximumRows, resources.size());
    for (std::size_t i = 0; i < rows; ++i) {
        const Resource& item = resources[i];
        std::cout << std::left
                  << std::setw(4) << item.id
                  << std::setw(kNameWidth) << item.name.substr(0, kNameWidth - 1)
                  << std::setw(12) << item.level
                  << std::setw(8) << std::fixed << std::setprecision(1) << item.rating
                  << std::setw(10) << (std::to_string(item.durationHours) + " jam")
                  << item.type << "\n";
    }
}

std::string chooseTopic(const Graph& graph, const std::string& label) {
    const std::vector<std::string> topics = getAllTopics(graph);
    std::cout << "\nDAFTAR TOPIK\n";
    for (std::size_t i = 0; i < topics.size(); ++i) {
        std::cout << std::setw(2) << (i + 1) << ". " << topics[i] << "\n";
    }
    const int selected = readInteger(label, 1, static_cast<int>(topics.size()));
    return topics[static_cast<std::size_t>(selected - 1)];
}

std::string chooseSortField() {
    std::cout << "\nField pengurutan:\n";
    std::cout << "1. Nama\n2. Rating\n3. Durasi\n4. Level\n";
    const int choice = readInteger("Pilih field [1-4]: ", 1, 4);
    if (choice == 1) return "name";
    if (choice == 2) return "rating";
    if (choice == 3) return "duration";
    return "level";
}

bool chooseDescending() {
    return readInteger("Urutan 1=Menaik, 2=Menurun: ", 1, 2) == 2;
}

void printMetrics(std::size_t comparisons, double elapsedMilliseconds, const std::string& complexity) {
    std::cout << "\nMetrik algoritma:\n";
    std::cout << "- Jumlah perbandingan : " << comparisons << "\n";
    std::cout << "- Waktu eksekusi      : " << std::fixed << std::setprecision(6)
              << elapsedMilliseconds << " ms\n";
    std::cout << "- Kompleksitas waktu  : " << complexity << "\n";
}

void printComplexityTable(const std::vector<ComplexityInfo>& table) {
    std::cout << "\nTABEL KOMPLEKSITAS BIG O\n";
    std::cout << std::left
              << std::setw(20) << "Algoritma"
              << std::setw(15) << "Best"
              << std::setw(15) << "Average"
              << std::setw(15) << "Worst"
              << "Space\n";
    std::cout << std::string(75, '-') << "\n";
    for (const ComplexityInfo& item : table) {
        std::cout << std::left
                  << std::setw(20) << item.algorithm
                  << std::setw(15) << item.bestCase
                  << std::setw(15) << item.averageCase
                  << std::setw(15) << item.worstCase
                  << item.space << "\n";
    }
}

void runDemo() {
    const Graph graph = createAiLearningGraph();
    const std::vector<Resource> resources = createAiResources();

    printHeader();
    std::cout << "MODE DEMONSTRASI OTOMATIS\n\n";

    std::cout << "[1] Jalur belajar tercepat: Mulai -> Generative AI\n";
    printPath(bfsShortestPath(graph, "Mulai", "Generative AI"));

    std::cout << "\n[2] Lima simpul awal traversal DFS dari Mulai\n";
    const std::vector<std::string> dfs = dfsTraversal(graph, "Mulai");
    printTraversal({dfs.begin(), dfs.begin() + static_cast<long>(std::min<std::size_t>(5, dfs.size()))});

    std::cout << "\n[3] Linear Search dengan kata kunci 'AI'\n";
    const SearchResult search = linearSearch(resources, "AI");
    printResourceTable(search.resources, 6);
    printMetrics(search.comparisons, search.elapsedMilliseconds, "O(n)");

    std::cout << "\n[4] Merge Sort berdasarkan rating tertinggi\n";
    const SortResult sorted = mergeSort(resources, "rating", true);
    printResourceTable(sorted.resources, 5);
    printMetrics(sorted.comparisons, sorted.elapsedMilliseconds, "O(n log n)");

    std::cout << "\nDemonstrasi selesai. Jalankan tanpa --demo untuk menu interaktif.\n";
}
}  // namespace

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runDemo();
        return 0;
    }

    const Graph graph = createAiLearningGraph();
    const std::vector<Resource> resources = createAiResources();
    const std::vector<ComplexityInfo> complexityTable = createComplexityTable();

    printHeader();
    while (true) {
        printMenu();
        const int choice = readInteger("Pilih menu [0-10]: ", 0, 10);
        std::cout << "\n";

        if (choice == 0) {
            std::cout << "Terima kasih telah menggunakan AI Learning Navigator.\n";
            break;
        }

        switch (choice) {
            case 1:
                printGraph(graph);
                break;
            case 2: {
                const std::string start = chooseTopic(graph, "Pilih simpul awal: ");
                std::cout << "\nHASIL BFS DARI " << start << "\n";
                printTraversal(bfsTraversal(graph, start));
                std::cout << "Kompleksitas: O(V + E)\n";
                break;
            }
            case 3: {
                const std::string start = chooseTopic(graph, "Pilih simpul awal: ");
                std::cout << "\nHASIL DFS DARI " << start << "\n";
                printTraversal(dfsTraversal(graph, start));
                std::cout << "Kompleksitas: O(V + E)\n";
                break;
            }
            case 4: {
                const std::string start = chooseTopic(graph, "Pilih kemampuan awal: ");
                const std::string target = chooseTopic(graph, "Pilih target belajar: ");
                std::cout << "\nJALUR TERPENDEK BFS\n";
                printPath(bfsShortestPath(graph, start, target));
                std::cout << "BFS menjamin jumlah edge paling sedikit pada graph tanpa bobot.\n";
                break;
            }
            case 5: {
                const std::string start = chooseTopic(graph, "Pilih kemampuan awal: ");
                const std::string target = chooseTopic(graph, "Pilih target belajar: ");
                std::cout << "\nJALUR EKSPLORASI DFS\n";
                printPath(dfsPath(graph, start, target));
                std::cout << "DFS menemukan salah satu jalur, tetapi tidak selalu yang terpendek.\n";
                break;
            }
            case 6: {
                const std::string query = readText("Masukkan kata kunci: ");
                const SearchResult result = linearSearch(resources, query);
                std::cout << "\nHASIL LINEAR SEARCH\n";
                printResourceTable(result.resources);
                printMetrics(result.comparisons, result.elapsedMilliseconds, "O(n)");
                break;
            }
            case 7: {
                const SortResult sortedByName = mergeSort(resources, "name", false);
                const std::string query = readText("Masukkan nama resource secara lengkap: ");
                const BinarySearchResult result = binarySearchExact(sortedByName.resources, query);
                std::cout << "\nHASIL BINARY SEARCH\n";
                if (result.found) {
                    printResourceTable({result.resource});
                } else {
                    std::cout << "Resource tidak ditemukan. Pastikan nama ditulis lengkap.\n";
                }
                printMetrics(result.comparisons, result.elapsedMilliseconds, "O(log n)");
                break;
            }
            case 8: {
                const std::string field = chooseSortField();
                const bool descending = chooseDescending();
                const SortResult result = bubbleSort(resources, field, descending);
                std::cout << "\nHASIL BUBBLE SORT\n";
                printResourceTable(result.resources);
                printMetrics(result.comparisons, result.elapsedMilliseconds, "O(n^2)");
                std::cout << "- Jumlah pertukaran   : " << result.swapsOrMoves << "\n";
                break;
            }
            case 9: {
                const std::string field = chooseSortField();
                const bool descending = chooseDescending();
                const SortResult result = mergeSort(resources, field, descending);
                std::cout << "\nHASIL MERGE SORT\n";
                printResourceTable(result.resources);
                printMetrics(result.comparisons, result.elapsedMilliseconds, "O(n log n)");
                std::cout << "- Jumlah pemindahan   : " << result.swapsOrMoves << "\n";
                break;
            }
            case 10:
                printComplexityTable(complexityTable);
                break;
            default:
                break;
        }

        readText("\nTekan Enter untuk kembali ke menu...");
    }
    return 0;
}
