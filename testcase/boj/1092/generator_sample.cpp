#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 35);
    int cap = rnd.next(8, 80);

    vector<int> cranes;
    vector<int> boxes;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) cranes.push_back(rnd.next(1, cap));
        sort(cranes.begin(), cranes.end());
        int maxCrane = cranes.back();
        for (int i = 0; i < m; ++i) boxes.push_back(rnd.next(1, maxCrane));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) cranes.push_back(rnd.next(1, cap));
        int maxCrane = *max_element(cranes.begin(), cranes.end());
        for (int i = 0; i + 1 < m; ++i) boxes.push_back(rnd.next(1, maxCrane));
        boxes.push_back(rnd.next(maxCrane + 1, maxCrane + 20));
    } else if (mode == 2) {
        int weak = rnd.next(1, 12);
        int strong = rnd.next(weak, weak + 8);
        for (int i = 0; i < n; ++i) cranes.push_back(rnd.next(0, 2) == 0 ? weak : strong);
        for (int i = 0; i < m; ++i) {
            int kind = rnd.next(0, 3);
            if (kind == 0) boxes.push_back(weak);
            else if (kind == 1) boxes.push_back(strong);
            else boxes.push_back(rnd.next(1, strong));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        m = rnd.next(n, 45);
        int base = rnd.next(10, 60);
        for (int i = 0; i < n; ++i) cranes.push_back(base + i * rnd.next(1, 4));
        for (int i = 0; i < m; ++i) boxes.push_back(rnd.next(max(1, base - 8), cranes.back()));
    } else if (mode == 4) {
        n = 1;
        m = rnd.next(1, 25);
        int limit = rnd.next(1, 100);
        cranes.push_back(limit);
        for (int i = 0; i < m; ++i) boxes.push_back(rnd.next(1, limit));
    } else {
        n = rnd.next(20, 50);
        m = rnd.next(40, 120);
        int low = rnd.next(1, 40);
        int high = rnd.next(low, low + 60);
        for (int i = 0; i < n; ++i) cranes.push_back(rnd.next(low, high));
        int maxCrane = *max_element(cranes.begin(), cranes.end());
        for (int i = 0; i < m; ++i) boxes.push_back(rnd.next(1, maxCrane));
    }

    if (rnd.next(0, 1)) shuffle(cranes.begin(), cranes.end());
    if (rnd.next(0, 1)) shuffle(boxes.begin(), boxes.end());

    println((int)cranes.size());
    println(cranes);
    println((int)boxes.size());
    println(boxes);

    return 0;
}
