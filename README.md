# AI Learning Navigator - C++17

AI Learning Navigator adalah aplikasi console interaktif bertema Artificial Intelligence. Aplikasi membantu pengguna menentukan jalur belajar AI, mencari resource, dan mengurutkan rekomendasi sambil mendemonstrasikan struktur data dan algoritma.

## Materi yang diterapkan

- Graph dengan adjacency list (`std::map<std::string, std::vector<std::string>>`)
- Breadth First Search (BFS)
- Depth First Search (DFS)
- Linear Search
- Binary Search
- Bubble Sort
- Merge Sort
- Analisis Big O

## Manfaat bagi pengguna

- Menemukan jalur belajar AI dengan jumlah tahap paling sedikit menggunakan BFS.
- Mengeksplorasi salah satu jalur pembelajaran secara mendalam menggunakan DFS.
- Mencari resource berdasarkan nama, kategori, level, atau tipe.
- Mengurutkan resource berdasarkan nama, rating, durasi, dan level.
- Membandingkan jumlah operasi, waktu eksekusi, serta kompleksitas algoritma.

## Persyaratan

- Compiler C++ yang mendukung C++17, misalnya GCC/MinGW-w64, Clang, atau MSVC.
- Tidak menggunakan library pihak ketiga.
- Tidak membutuhkan Python.

## Kompilasi cepat

### Windows dengan MinGW-w64

Jalankan:

```bat
build_windows.bat
```

Kemudian:

```bat
run_windows.bat
```

Atau melalui terminal:

```bash
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude src/main.cpp src/algorithms.cpp src/data.cpp -o ai_learning_navigator.exe
ai_learning_navigator.exe
```

### Linux/macOS

```bash
make
./bin/ai_learning_navigator
```

### CMake

```bash
cmake -S . -B build
cmake --build build
./build/ai_learning_navigator
```

## Pengujian

Dengan Make:

```bash
make test
```

Dengan CMake:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Mode demonstrasi

```bash
./bin/ai_learning_navigator --demo
```

## Struktur folder

- `include/models.hpp` - struktur data Resource dan hasil algoritma.
- `include/data.hpp` - deklarasi dataset graph dan resource.
- `include/algorithms.hpp` - deklarasi fungsi algoritma.
- `src/data.cpp` - graph topik AI, dataset resource, dan tabel Big O.
- `src/algorithms.cpp` - BFS, DFS, searching, dan sorting.
- `src/main.cpp` - menu aplikasi console.
- `tests/test_algorithms.cpp` - delapan pengujian dengan `assert`.
- `CMakeLists.txt` dan `Makefile` - konfigurasi build.

## Catatan Binary Search

Binary Search membutuhkan data yang sudah terurut. Program mengurutkan resource berdasarkan nama menggunakan Merge Sort sebelum menjalankan Binary Search.
