#include "../include/JHashTable.h"
#include <functional>
#include <iostream>
#include <random>
using namespace std;

int main() {
    JHashTable<int, int, hash<int>, equal_to<int>> table(10000);
    default_random_engine en;
    uniform_int_distribution<int> dist(-100000, 100000);

    for (int i = 0; i < 10000; i++) {
        int key = dist(en);
        int value = dist(en);
        table.insert(key, value);
    }

    cout << table.size() << endl;
    cout << (double)table.empty_bucket_count() / 10000.0 << endl;


}