#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>

struct SortResult {
    std::vector<std::string> sortedData;
    double executionTime;
};

// Generate random data
std::vector<std::string> generateRandomData(int size) {
    std::vector<std::string> data;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    
    for (int i = 0; i < size; i++) {
        char letter = 'A' + (rand() % 26);
        std::string item = std::string(1, letter) + 
                          (dis(gen) < 10 ? "0" : "") + 
                          std::to_string(dis(gen));
        data.push_back(item);
    }
    return data;
}

// Brute Force Sort
SortResult bruteForceSortWithTime(std::vector<std::string> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> data = arr;
    std::vector<std::string> sortedData;
    
    while (!data.empty()) {
        auto minElement = std::min_element(data.begin(), data.end());
        sortedData.push_back(*minElement);
        data.erase(minElement);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double, std::milli>(end - start).count();
    return {sortedData, time};
}

// Greedy Sort (Selection Sort)
SortResult greedySortWithTime(std::vector<std::string> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> data = arr;
    
    for (size_t i = 0; i < data.size(); i++) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < data.size(); j++) {
            if (data[j] < data[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(data[i], data[minIdx]);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double, std::milli>(end - start).count();
    return {data, time};
}

// Bubble Sort
SortResult bubbleSortWithTime(std::vector<std::string> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> data = arr;
    
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data.size() - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double, std::milli>(end - start).count();
    return {data, time};
}

// Insertion Sort
SortResult insertionSortWithTime(std::vector<std::string> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> data = arr;
    
    for (size_t i = 1; i < data.size(); i++) {
        std::string key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double, std::milli>(end - start).count();
    return {data, time};
}

// Merge Sort helper
void merge(std::vector<std::string>& arr, int left, int mid, int right) {
    std::vector<std::string> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<std::string> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    
    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < leftArr.size()) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < rightArr.size()) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSortImpl(std::vector<std::string>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortImpl(arr, left, mid);
        mergeSortImpl(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Merge Sort
SortResult mergeSortWithTime(std::vector<std::string> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> data = arr;
    
    mergeSortImpl(data, 0, data.size() - 1);
    
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double, std::milli>(end - start).count();
    return {data, time};
}

// Print data
void printData(const std::vector<std::string>& data, const std::string& label) {
    std::cout << label << ":\n";
    for (const auto& item : data) {
        std::cout << item << " ";
    }
    std::cout << "\n\n";
}

int main() {
    int problemSize;
    int iterations;
    
    std::cout << "Enter problem size: ";
    std::cin >> problemSize;
    std::cout << "Enter number of iterations: ";
    std::cin >> iterations;
    
    std::vector<std::string> originalData = generateRandomData(problemSize);
    printData(originalData, "Original Data");
    
    // Perform sorting and measure average times
    std::vector<double> avgTimes(5, 0.0);
    std::vector<std::vector<std::string>> sortedResults(5);
    
    for (int i = 0; i < iterations; i++) {
        auto bruteResult = bruteForceSortWithTime(originalData);
        auto greedyResult = greedySortWithTime(originalData);
        auto bubbleResult = bubbleSortWithTime(originalData);
        auto insertionResult = insertionSortWithTime(originalData);
        auto mergeResult = mergeSortWithTime(originalData);
        
        avgTimes[0] += bruteResult.executionTime;
        avgTimes[1] += greedyResult.executionTime;
        avgTimes[2] += bubbleResult.executionTime;
        avgTimes[3] += insertionResult.executionTime;
        avgTimes[4] += mergeResult.executionTime;
        
        if (i == 0) {
            sortedResults[0] = bruteResult.sortedData;
            sortedResults[1] = greedyResult.sortedData;
            sortedResults[2] = bubbleResult.sortedData;
            sortedResults[3] = insertionResult.sortedData;
            sortedResults[4] = mergeResult.sortedData;
        }
    }
    
    // Print results
    std::vector<std::string> algorithmNames = {
        "Brute Force", "Greedy", "Bubble", "Insertion", "Merge"
    };
    
    std::cout << "\nResults for " << problemSize << " items, averaged over " 
              << iterations << " iterations:\n\n";
    
    for (size_t i = 0; i < algorithmNames.size(); i++) {
        std::cout << std::fixed << std::setprecision(3);
        std::cout << algorithmNames[i] << " Sort:\n";
        std::cout << "Average Time: " << avgTimes[i]/iterations << " ms\n";
        printData(sortedResults[i], "Sorted Data");
    }
    
    return 0;
}