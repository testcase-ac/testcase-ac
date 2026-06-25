#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int clampValue(int value, int lo, int hi) {
    return max(lo, min(value, hi));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 30 : 12);
    int q = rnd.next(1, mode == 5 ? 80 : 25);

    vector<pair<int, int>> segments;
    segments.reserve(n);

    if (mode == 0) {
        int baseP = rnd.next(1, 20);
        int baseL = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int p = clampValue(baseP + rnd.next(-2, 2), 1, 10000);
            int l = clampValue(baseL + rnd.next(-5, 5), 1, 10000);
            segments.emplace_back(p, l);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(1, 40);
            int l = rnd.next(1, 40);
            if (rnd.next(0, 3) == 0) l = p;
            segments.emplace_back(p, l);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(1, 100);
            int l = rnd.next(1, 100);
            if (i % 3 == 0) p = 10000;
            if (i % 3 == 1) l = 10000;
            segments.emplace_back(p, l);
        }
    } else if (mode == 3) {
        int price = rnd.next(1, 70);
        for (int i = 0; i < n; ++i) {
            int l = rnd.next(1, 120);
            segments.emplace_back(price, l);
        }
    } else if (mode == 4) {
        int length = rnd.next(1, 90);
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(1, 120);
            segments.emplace_back(p, length);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(1, 300);
            int l = rnd.next(1, 300);
            segments.emplace_back(p, l);
        }
    }

    if (rnd.next(0, 1) == 0) {
        sort(segments.begin(), segments.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    } else {
        shuffle(segments.begin(), segments.end());
    }

    vector<pair<int, int>> queries;
    queries.reserve(q);

    for (int i = 0; i < q; ++i) {
        int kind = rnd.next(0, 5);
        if (kind <= 2) {
            vector<int> order(n);
            iota(order.begin(), order.end(), 0);
            shuffle(order.begin(), order.end());
            int take = rnd.next(1, n);
            int sumP = 0;
            int sumL = 0;
            int maxL = 0;
            for (int j = 0; j < take; ++j) {
                auto [p, l] = segments[order[j]];
                sumP += p;
                sumL += l;
                maxL = max(maxL, l);
            }

            int b;
            if (kind == 0) {
                b = rnd.next(maxL, sumL);
            } else if (kind == 1) {
                b = maxL;
            } else {
                b = sumL;
            }
            queries.emplace_back(clampValue(sumP, 1, 1000000), clampValue(b, 1, 1000000));
        } else if (kind == 3) {
            auto [p, l] = rnd.any(segments);
            int a = clampValue(p + rnd.next(-3, 3), 1, 1000000);
            int b = clampValue(l + rnd.next(-5, 5), 1, 1000000);
            queries.emplace_back(a, b);
        } else if (kind == 4) {
            queries.emplace_back(rnd.next(1, 1000000), rnd.next(1, 1000000));
        } else {
            int a = rnd.next(1, 200);
            int b = rnd.next(1, 200);
            if (rnd.next(0, 2) == 0) b = 1000000;
            queries.emplace_back(a, b);
        }
    }

    println(n, q);
    for (auto [p, l] : segments) println(p, l);
    for (auto [a, b] : queries) println(a, b);

    return 0;
}
