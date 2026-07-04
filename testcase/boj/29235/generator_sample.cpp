#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Fighter {
    long long a;
    long long b;
};

vector<int> positiveComposition(int n, int total) {
    vector<int> parts(n, 1);
    for (int remaining = total - n; remaining > 0; --remaining) {
        parts[rnd.next(n)]++;
    }
    return parts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 12);
    vector<Fighter> fighters;
    long long k = 1;

    if (mode == 0) {
        k = rnd.next(n, n + 35);
        vector<int> lengths = positiveComposition(n, static_cast<int>(k));
        fighters.reserve(n);
        for (int length : lengths) {
            long long a = rnd.next(0, length);
            long long b = rnd.next(length, length + 8);
            fighters.push_back({a, b});
        }
    } else if (mode == 1) {
        k = rnd.next(n + 5, n + 45);
        long long capacity = rnd.next(n, static_cast<int>(k) - 1);
        vector<int> caps = positiveComposition(n, static_cast<int>(capacity));
        fighters.reserve(n);
        for (int cap : caps) {
            long long a = rnd.next(0, cap);
            fighters.push_back({a, cap});
        }
    } else if (mode == 2) {
        n = rnd.next(1, 12);
        k = rnd.next(1, 35);
        long long demand = max<long long>(n, k + 1) + rnd.next(0, 12);
        vector<int> mins = positiveComposition(n, static_cast<int>(demand));
        fighters.reserve(n);
        for (int minValue : mins) {
            long long b = minValue + rnd.next(0, 8);
            fighters.push_back({minValue, b});
        }
    } else if (mode == 3) {
        k = rnd.next(1, 40);
        fighters.reserve(n);
        for (int i = 0; i < n; ++i) {
            long long a = (i == 0) ? rnd.next(1, 10) : rnd.next(0, 10);
            long long b = rnd.next(0LL, max(0LL, a - 1));
            fighters.push_back({a, b});
        }
    } else {
        k = rnd.next(n, n + 25);
        vector<int> lengths = positiveComposition(n, static_cast<int>(k));
        fighters.reserve(n);
        for (int i = 0; i < n; ++i) {
            int length = lengths[i];
            long long a = rnd.next(0, min(2, length));
            long long b = length + rnd.next(0, i % 3 == 0 ? 0 : 5);
            fighters.push_back({a, b});
        }
        shuffle(fighters.begin(), fighters.end());
    }

    println(n, k);
    for (const Fighter& fighter : fighters) {
        println(fighter.a, fighter.b);
    }

    return 0;
}
