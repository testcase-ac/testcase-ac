#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int mode = rnd.next(0, 5);
    vector<int> a;

    if (mode == 0) {
        int n = rnd.next(2, 18);
        int start = rnd.next(1, 1000000000 - n + 1);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + i);
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 16);
        a.push_back(1);
        a.push_back(1000000000);
        while ((int)a.size() < n) {
            int x = rnd.next(2, 999999999);
            if (find(a.begin(), a.end(), x) == a.end()) {
                a.push_back(x);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 20);
        int start = rnd.next(1, 999999000);
        int step = rnd.next(2, 25);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + i * step);
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 22);
        int center = rnd.next(100, 999999900);
        set<int> values;
        values.insert(center);
        while ((int)values.size() < n) {
            int offset = rnd.next(-60, 60);
            values.insert(center + offset);
        }
        a.assign(values.begin(), values.end());
    } else if (mode == 4) {
        int n = rnd.next(4, 24);
        int start = rnd.next(1, 999999000);
        int x = start;
        a.push_back(x);
        for (int i = 1; i < n; ++i) {
            int gap;
            if (i % 3 == 0) {
                gap = rnd.next(15, 80);
            } else {
                gap = rnd.next(1, 6);
            }
            x += gap;
            a.push_back(x);
        }
    } else {
        int n = rnd.next(2, 30);
        set<int> values;
        while ((int)values.size() < n) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                values.insert(rnd.next(1, 80));
            } else if (bucket == 1) {
                values.insert(rnd.next(999999920, 1000000000));
            } else {
                values.insert(rnd.next(100000, 100500));
            }
        }
        a.assign(values.begin(), values.end());
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);

    return 0;
}
