//
// Created by jiahua on 2018/12/17.
//
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <random>
#include <vector>
#include "Point3D.h"

using namespace std;
typedef unsigned long long ST;

const ST TOTAL = 50000000;

int main(int argc, const char **argv) {
    default_random_engine en;
    en.seed(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(1, 100000);
    uniform_int_distribution<ST> dist2(0, TOTAL - 1);
    vector<Point3D> data;

    data.reserve(TOTAL);
    for (int i = 0; i < TOTAL; i++)
        data.push_back({dist(en), dist(en), dist(en)});


    {
        unordered_map<Point3D, int, PointHash, PointEqual> hashTable;
        hashTable.reserve(TOTAL);
        auto start1 = chrono::steady_clock::now();
        for (ST i = 0; i < TOTAL; i++) {
            hashTable.insert({data[i], 10});
        }
        auto stop1 = chrono::steady_clock::now();
        auto elapsed_time1 = chrono::duration_cast<chrono::milliseconds>(stop1 - start1);
        cout << elapsed_time1.count() << " ms" << endl;
    }

    {
        vector<pair<Point3D, int>> linearTable(TOTAL);
        Point3D point{0, 0, 0};
        linearTable.resize(TOTAL, {point, 0});
        PointHash hash;
        auto start2 = chrono::steady_clock::now();
        for (ST i = 0; i < TOTAL; i++) {
            linearTable[hash(data[i]) % TOTAL] = {data[i], 10};
        }
        auto stop2 = chrono::steady_clock::now();
        auto elapsed_time2 = chrono::duration_cast<chrono::milliseconds>(stop2 - start2);
        cout << elapsed_time2.count() << " ms" << endl;

        ST count = 0;
        for (ST i = 0; i < TOTAL; i++) {
            if (linearTable[i].second == 10) ++count;
        }
        cout << fixed << ((double)count / (double)TOTAL) << endl;
    }


    return 0;
}

