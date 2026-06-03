#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> chooseAlgorithms(int k, int mode) {
    vector<int> algorithms;
    for (int i = 1; i <= k; ++i) {
        algorithms.push_back(i);
    }
    shuffle(algorithms.begin(), algorithms.end());

    int m = 0;
    if (mode == 0) {
        m = rnd.next(0, k);
    } else if (mode == 1) {
        m = rnd.next(0, min(k, 2));
    } else if (mode == 2) {
        m = rnd.next(max(0, k - 2), k);
    } else {
        m = rnd.next(0, k);
        if (rnd.next(4) == 0) {
            m = 0;
        }
    }

    algorithms.resize(m);
    sort(algorithms.begin(), algorithms.end());
    return algorithms;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, mode == 4 ? 24 : 14);
    int k = rnd.next(1, 30);
    long long d;

    vector<long long> skill(n);
    if (mode == 0) {
        d = rnd.next(0, 8);
        long long base = rnd.next(0, 60);
        for (int i = 0; i < n; ++i) {
            skill[i] = base + rnd.next(0, (int)d);
        }
    } else if (mode == 1) {
        d = rnd.next(0, 12);
        long long base = rnd.next(0, 80);
        for (int i = 0; i < n; ++i) {
            skill[i] = base + (long long)i * (d + 1) + rnd.next(0, 1);
        }
    } else if (mode == 2) {
        d = rnd.next(1, 20);
        long long base = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            skill[i] = base + rnd.next(0, (int)d + 2);
        }
    } else if (mode == 3) {
        d = 1000000000LL;
        for (int i = 0; i < n; ++i) {
            skill[i] = rnd.next(0, 1000000000);
        }
    } else {
        d = rnd.next(0, 1000000000);
        for (int i = 0; i < n; ++i) {
            skill[i] = rnd.next(0, 1000000000);
        }
    }

    vector<vector<int>> known(n);
    int algorithmMode = rnd.next(4);
    for (int i = 0; i < n; ++i) {
        known[i] = chooseAlgorithms(k, algorithmMode);
        if (mode == 2 && i % 3 == 0) {
            known[i].clear();
        }
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    println(n, k, d);
    for (int id : order) {
        println((int)known[id].size(), skill[id]);
        if (known[id].empty()) {
            printf("\n");
        } else {
            println(known[id]);
        }
    }

    return 0;
}
