#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 40 : 18);
    int m = rnd.next(0, 120);

    vector<pair<int, int>> challenges;
    challenges.reserve(n);

    if (mode == 0) {
        int money = m;
        for (int i = 0; i < n; ++i) {
            int cost = rnd.next(0, max(0, money));
            int gain = rnd.next(cost, cost + rnd.next(0, 35));
            challenges.push_back({cost, gain});
            money += gain - cost;
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int cost = rnd.next(0, 180);
            int payoff = rnd.next(0, max(0, cost - rnd.next(0, 45)));
            challenges.push_back({cost, payoff});
        }
    } else if (mode == 2) {
        int money = m;
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                challenges.push_back({0, rnd.next(0, 50)});
                money += challenges.back().second;
            } else {
                int cost = rnd.next(0, min(200, money + 40));
                int payoff = rnd.next(0, 220);
                challenges.push_back({cost, payoff});
            }
        }
    } else if (mode == 3) {
        int base = rnd.next(0, 90);
        for (int i = 0; i < n; ++i) {
            int cost = max(0, base + rnd.next(-10, 80));
            int delta = rnd.next(-30, 60);
            int payoff = max(0, cost + delta);
            challenges.push_back({cost, payoff});
        }
    } else if (mode == 4) {
        int money = m;
        for (int i = 0; i < n; ++i) {
            int cost = rnd.next(max(0, money + 1), money + 80);
            int payoff = cost + rnd.next(0, 80);
            challenges.push_back({cost, payoff});
            if (rnd.next(0, 2) == 0) {
                challenges.push_back({rnd.next(0, max(0, money)), rnd.next(0, money + 60)});
                ++i;
            }
        }
    } else {
        n = rnd.next(20, 80);
        m = rnd.next(0, 1000000);
        for (int i = 0; i < n; ++i) {
            int center = rnd.next(0, 1000000);
            int cost = rnd.next(max(0, center - 1000), center);
            int payoff = rnd.next(max(0, center - 1000), min(1000000, center + 1000));
            challenges.push_back({cost, payoff});
        }
    }

    n = (int)challenges.size();
    shuffle(challenges.begin(), challenges.end());

    vector<int> a, b;
    a.reserve(n);
    b.reserve(n);
    for (auto [cost, payoff] : challenges) {
        a.push_back(cost);
        b.push_back(payoff);
    }

    println(n, m);
    println(a);
    println(b);

    return 0;
}
