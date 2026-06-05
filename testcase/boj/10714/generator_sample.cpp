#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 12);
    } else {
        n = rnd.next(6, 80);
    }

    vector<int> a;
    if (mode == 0) {
        int start = rnd.next(1, 100);
        int step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) a.push_back(start + i * step);
    } else if (mode == 1) {
        int low = rnd.next(1, 1000);
        int high = rnd.next(1000000000 - 1000, 1000000000);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a.push_back(high - i);
            } else {
                a.push_back(low + i);
            }
        }
    } else if (mode == 2) {
        int start = rnd.next(1, 1000000000 - n * 10);
        int current = start;
        for (int i = 0; i < n; ++i) {
            a.push_back(current);
            current += rnd.next(1, 10);
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 3) {
        set<int> used;
        while ((int)a.size() < n) {
            int block = rnd.next(0, 3);
            int value = rnd.next(block * 1000000 + 1, block * 1000000 + 100000);
            if (used.insert(value).second) a.push_back(value);
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) a.push_back(i + 1);
        int rotations = rnd.next(0, n - 1);
        rotate(a.begin(), a.begin() + rotations, a.end());
        for (int i = 0; i < n; i += 3) {
            int j = rnd.next(0, n - 1);
            swap(a[i], a[j]);
        }
    } else {
        set<int> used;
        while ((int)a.size() < n) {
            int value = rnd.next(1, 1000000000);
            if (used.insert(value).second) a.push_back(value);
        }
    }

    println(n);
    for (int value : a) println(value);

    return 0;
}
