#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 123456789123LL;

    int mode = rnd.next(0, 6);
    int t;
    if (mode == 0) {
        t = 1;
    } else if (mode == 1) {
        t = rnd.next(2, 8);
    } else if (mode == 2) {
        t = rnd.next(20, 80);
    } else if (mode == 3) {
        t = 1000;
    } else {
        t = rnd.next(3, 30);
    }

    vector<long long> values;
    values.reserve(t);

    auto add = [&](long long x) {
        if (1 <= x && x <= MAX_N && (int)values.size() < t) {
            values.push_back(x);
        }
    };

    if (mode == 0) {
        add(rnd.any(vector<long long>{1LL, 2LL, 3LL, MAX_N}));
    } else if (mode == 1) {
        for (int i = 1; i <= 20 && (int)values.size() < t; ++i) {
            add(i);
        }
    } else if (mode == 2) {
        for (int bit = 0; bit <= 36 && (int)values.size() < t; ++bit) {
            long long p = 1LL << bit;
            add(p);
            add(p - 1);
            add(p + 1);
        }
    } else if (mode == 3) {
        add(1);
        add(2);
        add(MAX_N);
        add(MAX_N - 1);
    } else {
        add(MAX_N);
        add(rnd.next(1LL, 1000LL));
    }

    while ((int)values.size() < t) {
        int choice = rnd.next(0, 4);
        if (choice == 0) {
            add(rnd.next(1LL, 100LL));
        } else if (choice == 1) {
            long long p = 1LL << rnd.next(0, 36);
            long long delta = rnd.next(-3LL, 3LL);
            add(p + delta);
        } else if (choice == 2) {
            add(rnd.next(1LL, 1000000LL));
        } else if (choice == 3) {
            add(rnd.next(MAX_N - 1000000LL, MAX_N));
        } else {
            add(rnd.next(1LL, MAX_N));
        }
    }

    shuffle(values.begin(), values.end());

    println(t);
    for (long long x : values) {
        println(x);
    }

    return 0;
}
