#include "data.hpp"

#include <set>

Graph createAiLearningGraph() {
    return {
        {"Mulai", {"Dasar Pemrograman C++", "Matematika Dasar", "Etika AI"}},
        {"Dasar Pemrograman C++", {"Struktur Data", "Pengolahan Data"}},
        {"Matematika Dasar", {"Statistika", "Aljabar Linear"}},
        {"Etika AI", {"Proyek AI"}},
        {"Struktur Data", {"Machine Learning"}},
        {"Pengolahan Data", {"Machine Learning"}},
        {"Statistika", {"Machine Learning"}},
        {"Aljabar Linear", {"Machine Learning", "Deep Learning"}},
        {"Machine Learning", {"Deep Learning", "Deployment AI", "Proyek AI"}},
        {"Deep Learning", {"Natural Language Processing", "Computer Vision", "Generative AI"}},
        {"Natural Language Processing", {"Generative AI", "Proyek AI"}},
        {"Computer Vision", {"Proyek AI"}},
        {"Generative AI", {"Deployment AI", "Proyek AI"}},
        {"Deployment AI", {"Proyek AI"}},
        {"Proyek AI", {}}
    };
}

std::vector<Resource> createAiResources() {
    return {
        {1, "C++ untuk Pemula", "Dasar Pemrograman C++", "Pemula", 4.7, 12, "Kursus"},
        {2, "Struktur Data Praktis", "Struktur Data", "Pemula", 4.6, 10, "Modul"},
        {3, "Pengolahan Dataset AI", "Pengolahan Data", "Pemula", 4.8, 8, "Kursus"},
        {4, "Statistika untuk Data Science", "Statistika", "Menengah", 4.7, 15, "Buku"},
        {5, "Aljabar Linear Visual", "Aljabar Linear", "Menengah", 4.5, 14, "Video"},
        {6, "Machine Learning Fundamental", "Machine Learning", "Menengah", 4.9, 24, "Kursus"},
        {7, "Klasifikasi Data dari Nol", "Machine Learning", "Menengah", 4.8, 9, "Praktikum"},
        {8, "Deep Learning Dasar", "Deep Learning", "Menengah", 4.8, 20, "Kursus"},
        {9, "Neural Network dari Nol", "Deep Learning", "Lanjutan", 4.6, 18, "Modul"},
        {10, "NLP Bahasa Indonesia", "Natural Language Processing", "Lanjutan", 4.7, 16, "Praktikum"},
        {11, "Computer Vision dengan OpenCV C++", "Computer Vision", "Menengah", 4.6, 14, "Kursus"},
        {12, "Pengenalan Generative AI", "Generative AI", "Pemula", 4.9, 6, "Seminar"},
        {13, "Prompt Engineering Efektif", "Generative AI", "Pemula", 4.8, 5, "Workshop"},
        {14, "MLOps dan Deployment Model", "Deployment AI", "Lanjutan", 4.7, 18, "Kursus"},
        {15, "Etika dan Keamanan AI", "Etika AI", "Pemula", 4.9, 4, "Modul"},
        {16, "Proyek Prediksi Harga", "Proyek AI", "Menengah", 4.6, 12, "Proyek"},
        {17, "Proyek Chatbot Layanan", "Proyek AI", "Lanjutan", 4.8, 20, "Proyek"},
        {18, "Matematika Dasar AI", "Matematika Dasar", "Pemula", 4.5, 11, "Buku"}
    };
}

std::vector<ComplexityInfo> createComplexityTable() {
    return {
        {"BFS", "O(V + E)", "O(V + E)", "O(V + E)", "O(V)"},
        {"DFS", "O(V + E)", "O(V + E)", "O(V + E)", "O(V)"},
        {"Linear Search", "O(1)", "O(n)", "O(n)", "O(1)"},
        {"Binary Search", "O(1)", "O(log n)", "O(log n)", "O(1)"},
        {"Bubble Sort", "O(n)", "O(n^2)", "O(n^2)", "O(1)"},
        {"Merge Sort", "O(n log n)", "O(n log n)", "O(n log n)", "O(n)"}
    };
}

std::vector<std::string> getAllTopics(const Graph& graph) {
    std::set<std::string> uniqueTopics;
    for (const auto& [node, neighbors] : graph) {
        uniqueTopics.insert(node);
        uniqueTopics.insert(neighbors.begin(), neighbors.end());
    }
    return {uniqueTopics.begin(), uniqueTopics.end()};
}
