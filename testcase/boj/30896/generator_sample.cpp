#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int clampScore(int x) {
    return max(1, min(100, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 12);
    } else {
        n = rnd.next(8, 30);
    }

    vector<pair<int, int>> people;
    people.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            people.emplace_back(rnd.any(vector<int>{1, 2, 99, 100}),
                                rnd.any(vector<int>{1, 2, 99, 100}));
        }
    } else if (mode == 1) {
        int a = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            people.emplace_back(a, rnd.next(1, 100));
        }
    } else if (mode == 2) {
        int b = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            people.emplace_back(rnd.next(1, 100), b);
        }
    } else if (mode == 3) {
        int lowA = rnd.next(1, 30);
        int highA = rnd.next(70, 100);
        for (int i = 0; i < n; ++i) {
            int a = (i < n / 2 ? rnd.next(lowA, min(100, lowA + 10))
                               : rnd.next(max(1, highA - 10), highA));
            int b = (i < n / 2 ? rnd.next(60, 100) : rnd.next(1, 40));
            people.emplace_back(a, b);
        }
    } else if (mode == 4) {
        int a = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a = clampScore(a + rnd.next(0, 6));
            people.emplace_back(a, rnd.next(1, 100));
        }
    } else {
        int maxA = rnd.next(10, 100);
        int maxB = rnd.next(10, 100);
        for (int i = 0; i < n; ++i) {
            people.emplace_back(rnd.next(1, maxA), rnd.next(1, maxB));
        }
    }

    shuffle(people.begin(), people.end());

    println(n);
    for (auto [a, b] : people) {
        println(a, b);
    }

    return 0;
}
