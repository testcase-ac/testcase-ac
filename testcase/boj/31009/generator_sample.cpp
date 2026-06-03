#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

string destinationName(int index) {
    string name = "a";
    while (index > 0) {
        name.push_back(char('a' + index % 26));
        index /= 26;
    }
    if (name == "jinju") {
        name = "jinjv";
    }
    return name;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(80, 160);
    } else {
        n = rnd.next(2, 20);
    }

    int jinjuCost;
    if (mode == 0) {
        jinjuCost = 1;
    } else if (mode == 1) {
        jinjuCost = 1000;
    } else if (mode == 2) {
        jinjuCost = rnd.next(2, 999);
    } else if (mode == 3) {
        jinjuCost = rnd.next(450, 550);
    } else if (mode == 4) {
        jinjuCost = rnd.any(vector<int>{1, 2, 999, 1000});
    } else {
        jinjuCost = rnd.next(100, 900);
    }

    vector<pair<string, int>> routes;
    routes.push_back({"jinju", jinjuCost});

    for (int i = 1; i < n; ++i) {
        int cost;
        if (mode == 0) {
            cost = rnd.next(1, 4) == 1 ? 1 : rnd.next(2, 1000);
        } else if (mode == 1) {
            cost = rnd.next(1, 4) == 1 ? 1000 : rnd.next(1, 999);
        } else if (mode == 2) {
            int delta = rnd.next(-3, 3);
            cost = min(1000, max(1, jinjuCost + delta));
        } else if (mode == 3) {
            cost = rnd.next(1, 1000);
        } else if (mode == 4) {
            cost = rnd.any(vector<int>{1, jinjuCost, 1000});
        } else {
            int band = rnd.next(0, 2);
            if (band == 0) {
                cost = rnd.next(1, max(1, jinjuCost - 1));
            } else if (band == 1) {
                cost = jinjuCost;
            } else {
                cost = rnd.next(min(1000, jinjuCost + 1), 1000);
            }
        }
        routes.push_back({destinationName(i), cost});
    }

    shuffle(routes.begin(), routes.end());

    println(n);
    for (const auto& [destination, cost] : routes) {
        println(destination, cost);
    }

    return 0;
}
