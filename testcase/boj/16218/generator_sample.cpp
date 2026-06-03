#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampPower(int x) {
    return max(0, min(60, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int k = rnd.next(100, 1000);
    vector<pair<int, int>> rounds;

    if (mode == 0) {
        n = rnd.next(1, 4);
        k = rnd.next(100, 160);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, 60);
            int b = rnd.next(0, 60);
            if (i == n - 1 && rnd.next(0, 1)) b = 60;
            rounds.push_back({a, b});
        }
    } else if (mode == 1) {
        n = rnd.next(5, 18);
        k = rnd.next(500, 1000);
        int base = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            int a = clampPower(base + rnd.next(0, 6));
            int b = clampPower(base + rnd.next(0, 6));
            rounds.push_back({a, b});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        k = rnd.next(100, 260);
        int lead = rnd.next(42, 49);
        rounds.push_back({clampPower(lead), 0});
        for (int i = 1; i < n; ++i) {
            int a = rnd.next(0, 12);
            int b = rnd.next(0, 8);
            rounds.push_back({a, b});
        }
    } else if (mode == 3) {
        n = rnd.next(4, 16);
        k = rnd.next(100, 300);
        for (int i = 0; i < n; ++i) {
            int a = rnd.any(vector<int>{1, 3, 5, 7, 9, 59});
            int b = rnd.next(0, 20);
            if (rnd.next(0, 2) == 0) swap(a, b);
            rounds.push_back({a, b});
        }
    } else if (mode == 4) {
        n = rnd.next(10, 30);
        k = rnd.next(100, 400);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(45, 60);
            int b = rnd.next(45, 60);
            rounds.push_back({a, b});
        }
    } else {
        n = rnd.next(1, 25);
        k = rnd.next(100, 1000);
        int maxA = rnd.next(0, 60);
        int maxB = rnd.next(0, 60);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, maxA);
            int b = rnd.next(0, maxB);
            rounds.push_back({a, b});
        }
    }

    if (rnd.next(0, 4) == 0) {
        shuffle(rounds.begin(), rounds.end());
    }

    println((int)rounds.size(), k);
    for (const auto& [a, b] : rounds) {
        println(a, b);
    }

    return 0;
}
