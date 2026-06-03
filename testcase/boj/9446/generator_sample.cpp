#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Rule {
    int a;
    int x;
    int y;
};

long long randomCost(int mode) {
    if (mode == 0) {
        return rnd.next(0, 20);
    }
    if (mode == 1) {
        return rnd.next(0, 1) ? rnd.next(0, 5) : rnd.next(100, 1000);
    }
    return rnd.next(0, 1) ? 0 : rnd.next(900000000, 1000000000);
}

Rule randomRule(int n) {
    int a = rnd.next(1, n);
    int x = rnd.next(1, n - 1);
    if (x >= a) {
        ++x;
    }

    int y = rnd.next(1, n - 2);
    int first = min(a, x);
    int second = max(a, x);
    if (y >= first) {
        ++y;
    }
    if (y >= second) {
        ++y;
    }

    if (rnd.next(0, 1)) {
        swap(x, y);
    }
    return {a, x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 0 ? rnd.next(1, 3) : rnd.next(3, 12);

    vector<long long> costs(n);
    int costMode = rnd.next(0, 2);
    for (int i = 0; i < n; ++i) {
        costs[i] = randomCost(costMode);
    }

    vector<Rule> rules;
    if (mode == 0 || n < 3) {
        rules.clear();
    } else if (mode == 1) {
        int m = rnd.next(1, min(8, n * 2));
        for (int i = 0; i < m; ++i) {
            rules.push_back(randomRule(n));
        }
    } else if (mode == 2) {
        int steps = rnd.next(1, min(5, n - 2));
        vector<int> items;
        for (int i = 2; i <= n; ++i) {
            items.push_back(i);
        }
        shuffle(items.begin(), items.end());

        int target = 1;
        for (int i = 0; i < steps; ++i) {
            int x = items[i];
            int y = items[(i + 1) % items.size()];
            rules.push_back({target, x, y});
            target = x;
        }

        int extras = rnd.next(0, 5);
        for (int i = 0; i < extras; ++i) {
            rules.push_back(randomRule(n));
        }
    } else {
        vector<Rule> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int x = 1; x <= n; ++x) {
                for (int y = x + 1; y <= n; ++y) {
                    if (a != x && a != y) {
                        Rule r = {a, x, y};
                        if (rnd.next(0, 1)) {
                            swap(r.x, r.y);
                        }
                        candidates.push_back(r);
                    }
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int m = rnd.next(n, min<int>(static_cast<int>(candidates.size()), 35));
        rules.assign(candidates.begin(), candidates.begin() + m);
    }

    println(n, static_cast<int>(rules.size()));
    println(costs);
    for (const Rule& rule : rules) {
        println(rule.a, rule.x, rule.y);
    }

    return 0;
}
