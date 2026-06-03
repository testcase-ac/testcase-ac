#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Operation = pair<char, long long>;

long long randomValue(bool preferExtreme) {
    if (preferExtreme && rnd.next(100) < 35) {
        vector<long long> values = {1, 2, 999999937LL, 999999999LL, 1000000000LL};
        return rnd.any(values);
    }
    if (rnd.next(100) < 70) {
        return rnd.next(1, 20);
    }
    return rnd.next(1LL, 1000000000LL);
}

char randomOp(int plusWeight) {
    return rnd.next(100) < plusWeight ? '+' : '*';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1, q = 1;
    bool preferExtreme = true;

    if (mode == 0) {
        n = rnd.next(1, 3);
        q = rnd.next(1, 6);
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        q = rnd.next(4, 16);
    } else if (mode == 2) {
        n = rnd.next(6, 18);
        q = rnd.next(6, 20);
    } else if (mode == 3) {
        n = rnd.next(8, 24);
        q = rnd.next(8, 24);
    } else {
        n = rnd.next(10, 30);
        q = rnd.next(10, 30);
        preferExtreme = rnd.next(100) < 55;
    }

    vector<Operation> initial(n);
    if (mode == 1) {
        int split = rnd.next(0, n);
        for (int i = 0; i < n; ++i) {
            initial[i] = {i < split ? '+' : '*', randomValue(preferExtreme)};
        }
    } else if (mode == 2) {
        char first = randomOp(50);
        for (int i = 0; i < n; ++i) {
            initial[i] = {i % 2 == 0 ? first : (first == '+' ? '*' : '+'), randomValue(preferExtreme)};
        }
    } else if (mode == 3) {
        int plusWeight = rnd.next(100) < 50 ? rnd.next(80, 100) : rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            initial[i] = {randomOp(plusWeight), randomValue(preferExtreme)};
        }
    } else {
        int plusWeight = rnd.next(25, 75);
        for (int i = 0; i < n; ++i) {
            initial[i] = {randomOp(plusWeight), randomValue(preferExtreme)};
        }
    }

    vector<int> hot;
    int hotCount = rnd.next(1, min(n, 4));
    for (int i = 1; i <= n; ++i) {
        hot.push_back(i);
    }
    shuffle(hot.begin(), hot.end());
    hot.resize(hotCount);

    vector<Operation> updates;
    vector<int> updateIndex;
    for (int j = 0; j < q; ++j) {
        int idx;
        if (rnd.next(100) < 60) {
            idx = rnd.any(hot);
        } else {
            idx = rnd.next(1, n);
        }

        int plusWeight = 50;
        if (mode == 1) plusWeight = rnd.next(100) < 65 ? 25 : 75;
        if (mode == 3) plusWeight = initial[idx - 1].first == '+' ? 20 : 80;

        updateIndex.push_back(idx);
        updates.push_back({randomOp(plusWeight), randomValue(preferExtreme)});
    }

    println(n, q);
    for (const auto& op : initial) {
        println(string(1, op.first), op.second);
    }
    for (int j = 0; j < q; ++j) {
        println(updateIndex[j], string(1, updates[j].first), updates[j].second);
    }

    return 0;
}
