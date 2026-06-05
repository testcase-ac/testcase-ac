#include "testlib.h"
#include <vector>

using namespace std;

int lit(int m) {
    int x = rnd.next(1, m);
    return rnd.next(0, 1) ? x : -x;
}

vector<pair<int, int>> makeRandomRules(int m, int n) {
    vector<pair<int, int>> rules;
    for (int i = 0; i < n; ++i) {
        rules.push_back({lit(m), lit(m)});
    }
    return rules;
}

vector<pair<int, int>> makeUnitPressure(int m, bool contradictory) {
    int x = rnd.next(1, m);
    vector<pair<int, int>> rules;
    rules.push_back({x, x});
    if (contradictory) {
        rules.push_back({-x, -x});
    }
    int extras = rnd.next(0, 4);
    for (int i = 0; i < extras; ++i) {
        int y = rnd.next(1, m);
        rules.push_back({rnd.next(0, 1) ? x : -x, rnd.next(0, 1) ? y : -y});
    }
    shuffle(rules.begin(), rules.end());
    return rules;
}

vector<pair<int, int>> makeAllPairsContradiction() {
    return {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 8);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 5);
        int m = rnd.next(1, 10);
        vector<pair<int, int>> rules;

        if (mode == 0) {
            rules = makeRandomRules(m, rnd.next(0, 2 * m));
        } else if (mode == 1) {
            rules = makeRandomRules(m, rnd.next(2 * m, 4 * m));
        } else if (mode == 2) {
            rules = makeUnitPressure(m, false);
        } else if (mode == 3) {
            rules = makeUnitPressure(m, true);
        } else if (mode == 4) {
            m = rnd.next(2, 5);
            rules = makeAllPairsContradiction();
            for (int i = 0; i < rnd.next(0, 4); ++i) {
                rules.push_back({lit(m), lit(m)});
            }
            shuffle(rules.begin(), rules.end());
        } else {
            rules = makeRandomRules(m, rnd.next(1, 12));
            int x = rnd.next(1, m);
            rules.push_back({x, -x});
            rules.push_back({-x, x});
        }

        println((int)rules.size(), m);
        for (auto rule : rules) {
            println(rule.first, rule.second);
        }
    }

    println(0, 0);
    return 0;
}
