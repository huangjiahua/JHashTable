#include "../include/JHashTable.h"
#include <functional>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
using namespace std;

const size_t TOTAL = 50000000;

int main() {
    JHashTable<int, int, hash<int>, equal_to<int>> table(TOTAL);
    default_random_engine en;
    uniform_int_distribution<int> dist(-1 * (int)TOTAL, (int)TOTAL);
    vector<int> data;
    data.reserve(TOTAL);

    for (int i = 0; i < TOTAL; i++)
        data.push_back(dist(en));


    auto start1 = chrono::steady_clock::now();
    for (int i = 0; i < TOTAL; i++) {
        table.force_insert(data[i], 10);
    }
    auto stop1 = chrono::steady_clock::now();

    cout << chrono::duration_cast<chrono::milliseconds>(stop1 - start1).count() << endl;
    cout << table.size() << endl;
    cout << (double)table.empty_bucket_count() / (double)TOTAL << endl;
}