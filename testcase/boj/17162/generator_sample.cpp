#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int valueForResidue(int residue, int mod) {
    if (rnd.next(5) == 0) {
        int maxK = (2147483647 - residue) / mod;
        int k = rnd.next(max(0, maxK - 20), maxK);
        long long value = 1LL * k * mod + residue;
        if (value >= 1 && value <= 2147483647) {
            return static_cast<int>(value);
        }
    }

    int base = max(1, residue);
    int k = rnd.next(0, 20);
    long long value = 1LL * k * mod + base;
    while (value % mod != residue) {
        ++value;
    }
    return static_cast<int>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int mod;
    if (mode == 0) {
        mod = rnd.next(1, 3);
    } else if (mode == 1) {
        mod = rnd.next(2, 8);
    } else if (mode == 2) {
        mod = rnd.next(8, 20);
    } else {
        mod = rnd.next(80, 100);
    }

    int targetQ = rnd.next(1, 80);
    vector<string> queries;
    vector<int> arr;

    auto pushValue = [&](int residue) {
        int value = valueForResidue(residue, mod);
        queries.push_back("1 " + to_string(value));
        arr.push_back(value % mod);
    };

    auto popValue = [&]() {
        queries.push_back("2");
        if (!arr.empty()) {
            arr.pop_back();
        }
    };

    auto ask = [&]() {
        queries.push_back("3");
    };

    if (mode == 0) {
        int leadingPops = rnd.next(0, min(5, targetQ - 1));
        for (int i = 0; i < leadingPops; ++i) {
            popValue();
        }
        ask();
    } else if (mode == 1) {
        int take = rnd.next(1, min(mod, targetQ - 1));
        for (int i = 0; i < take; ++i) {
            pushValue(i % mod);
        }
        ask();
    } else {
        vector<int> residues;
        for (int i = 0; i < mod; ++i) {
            residues.push_back(i);
        }
        shuffle(residues.begin(), residues.end());
        int take = min(mod, targetQ - 1);
        for (int i = 0; i < take; ++i) {
            pushValue(residues[i]);
        }
        ask();
    }

    while (static_cast<int>(queries.size()) < targetQ) {
        int remaining = targetQ - static_cast<int>(queries.size());
        int choice = rnd.next(0, 99);

        if (remaining == 1 || choice < 25) {
            ask();
        } else if (choice < 45) {
            popValue();
        } else {
            int residue;
            if (mode == 1 && !arr.empty() && rnd.next(2) == 0) {
                residue = rnd.any(arr);
            } else {
                residue = rnd.next(0, mod - 1);
            }
            pushValue(residue);
        }
    }

    println(static_cast<int>(queries.size()), mod);
    for (const string& query : queries) {
        println(query);
    }

    return 0;
}
