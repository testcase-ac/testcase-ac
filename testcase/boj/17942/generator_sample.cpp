#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    int m = rnd.next(1, n);

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, n);
    } else if (mode == 4) {
        n = rnd.next(8, 14);
        m = rnd.next(n / 2, n);
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    vector<long long> k(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (mode == 1) {
            k[i] = rnd.next(20, 80);
        } else if (mode == 2) {
            k[i] = rnd.next(2, 25);
        } else if (mode == 3) {
            k[i] = rnd.next(50, 120);
        } else {
            k[i] = rnd.next(1, 100);
        }
    }

    vector<long long> incoming(n + 1, 0);
    set<pair<int, int>> used;
    vector<pair<pair<int, int>, int>> relations;

    auto add_relation = [&](int a, int b, int preferred) {
        if (a == b || used.count({a, b})) {
            return;
        }

        long long room = k[b] - incoming[b] - 1;
        if (room <= 0) {
            return;
        }

        int d = rnd.next(1, static_cast<int>(min<long long>(room, preferred)));
        incoming[b] += d;
        used.insert({a, b});
        relations.push_back({{a, b}, d});
    };

    if (mode == 0) {
        if (n >= 2) {
            add_relation(order[0], order[1], 5);
        }
    } else if (mode == 1) {
        for (int i = 0; i + 1 < n; ++i) {
            int b = order[i + 1];
            add_relation(order[i], b, static_cast<int>(max(1LL, k[b] / 2)));
        }
        for (int i = 0; i + 2 < n; ++i) {
            if (rnd.next(0, 1)) {
                int b = order[i + 2];
                add_relation(order[i], b, static_cast<int>(max(1LL, k[b] / 3)));
            }
        }
    } else if (mode == 2) {
        int center = order[0];
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 1)) {
                add_relation(center, order[i], 8);
            } else {
                add_relation(order[i], center, 8);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            add_relation(order[i], order[(i + 1) % n], 35);
        }
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                add_relation(order[i], order[(i + 2) % n], 20);
            }
        }
    } else {
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (a != b) {
                    candidates.push_back({a, b});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());

        int target = rnd.next(n, min<int>(static_cast<int>(candidates.size()), 2 * n + 8));
        for (auto [a, b] : candidates) {
            if (static_cast<int>(relations.size()) >= target) {
                break;
            }
            add_relation(a, b, static_cast<int>(max(1LL, k[b] / 2)));
        }
    }

    shuffle(relations.begin(), relations.end());

    println(n, m);
    vector<long long> values(k.begin() + 1, k.end());
    println(values);
    println(static_cast<int>(relations.size()));
    for (auto relation : relations) {
        println(relation.first.first, relation.first.second, relation.second);
    }

    return 0;
}
