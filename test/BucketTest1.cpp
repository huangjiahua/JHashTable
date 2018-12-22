#include "../src/JHashBucket.h"
#include <utility>
#include <functional>
#include <iostream>
using namespace std;

int main() {
    JHashBucket<int, int, std::equal_to<>> bkt;

    std::equal_to<> e;
    for (int i = 0; i < 50; i++) {
        bkt.insert(i, i+1, e);
    }

    for (int i = 50; i < 55; i++) {
        bkt.force_insert(i, i+1);
    }


    cout << bkt.find(30, e)->value << endl;
    cout << bkt.size() << endl;

}