#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    vector<pair<string, int>> claims;

    auto add = [&](const string& kind, int p) {
        claims.push_back({kind, p});
    };

    if (mode == 0) {
        int center = rnd.next(0, 100);
        int spread = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            int p = max(0, center + rnd.next(-spread, spread));
            add(rnd.next(0, 1) == 0 ? "L" : "G", p);
        }
    } else if (mode == 1) {
        vector<int> values = {0, 1, 2, 999999998, 999999999, 1000000000};
        for (int i = 0; i < n; ++i) {
            add(rnd.next(0, 1) == 0 ? "L" : "G", rnd.any(values));
        }
    } else if (mode == 2) {
        int low = rnd.next(0, 30);
        int high = rnd.next(low, low + rnd.next(0, 20));
        add("G", high);
        add("L", low);
        while ((int)claims.size() < n) {
            int p = rnd.next(max(0, low - 5), high + 5);
            add(rnd.next(0, 1) == 0 ? "L" : "G", p);
        }
    } else if (mode == 3) {
        int p = rnd.next(0, 1000000000);
        for (int i = 0; i < n; ++i) {
            add(rnd.next(0, 1) == 0 ? "L" : "G", p);
        }
    } else if (mode == 4) {
        int base = rnd.next(0, 1000000000 - 40);
        for (int i = 0; i < n; ++i) {
            int p = base + rnd.next(0, 40);
            add(i % 3 == 0 ? "G" : "L", p);
        }
    } else {
        int p = rnd.next(0, 1000000000);
        add("G", p);
        while ((int)claims.size() < n) {
            int delta = rnd.next(0, 10);
            int q = rnd.next(0, 1) == 0 ? max(0, p - delta) : min(1000000000, p + delta);
            add(rnd.next(0, 1) == 0 ? "L" : "G", q);
        }
    }

    bool hasG = false;
    for (const auto& claim : claims) {
        hasG = hasG || claim.first == "G";
    }
    if (!hasG) {
        claims[rnd.next((int)claims.size())].first = "G";
    }

    shuffle(claims.begin(), claims.end());

    println((int)claims.size());
    for (const auto& claim : claims) {
        println(claim.first, claim.second);
    }

    return 0;
}
