#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const long long MIN_A = -2000000000LL;
const long long MAX_A = 2000000000LL;

void printArray(const vector<long long>& a) {
    println((int)a.size());
    for (long long x : a) println(x);
}

vector<long long> shuffledRange(int n, long long first, long long step) {
    vector<long long> a;
    for (int i = 0; i < n; ++i) a.push_back(first + step * i);
    shuffle(a.begin(), a.end());
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 45);
    if (rnd.next(0, 9) == 0) n = rnd.next(46, 120);

    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 6);
        vector<long long> pool = {MIN_A, MAX_A, -1, 0, 1, rnd.next(-1000000, 1000000)};
        set<long long> used;
        for (long long x : pool) {
            if ((int)a.size() == n) break;
            if (used.insert(x).second) a.push_back(x);
        }
        while ((int)a.size() < n) {
            long long x = rnd.next(-2000000000, 2000000000);
            if (used.insert(x).second) a.push_back(x);
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        long long start = rnd.next(-2000000000, 2000000000 - n);
        for (int i = 0; i < n; ++i) a.push_back(start + i);
    } else if (mode == 2) {
        long long start = rnd.next(-2000000000 + n, 2000000000);
        for (int i = 0; i < n; ++i) a.push_back(start - i);
    } else if (mode == 3) {
        long long start = rnd.next(-1000000, 1000000);
        long long step = rnd.next(1, 17);
        a = shuffledRange(n, start, step);
    } else if (mode == 4) {
        set<long long> used;
        while ((int)a.size() < n) {
            long long x;
            if (rnd.next(0, 2) == 0) {
                x = rnd.next(-30, 30);
            } else {
                x = rnd.next(-2000000000, 2000000000);
            }
            if (used.insert(x).second) a.push_back(x);
        }
    } else if (mode == 5) {
        int base = rnd.next(-5000, 5000);
        for (int i = 0; i < n; ++i) {
            long long x = base + (i / 2) * 3;
            if (i % 2 == 1) x = base - 10000 - (i / 2) * 3;
            a.push_back(x);
        }
    } else {
        n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            long long x = (i % 2 == 0 ? MIN_A + i / 2 : MAX_A - i / 2);
            a.push_back(x);
        }
        shuffle(a.begin(), a.end());
    }

    printArray(a);
    return 0;
}
