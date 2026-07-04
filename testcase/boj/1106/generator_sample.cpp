#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int C = rnd.next(1, 1000);
    vector<pair<int, int>> cities;

    if (mode == 0) {
        int gain = rnd.next(1, 100);
        C = rnd.next(1, 1000);
        cities.push_back({rnd.next(1, 100), gain});
        cities.push_back({rnd.next(1, 100), gain});
        cities.push_back({rnd.next(1, 100), rnd.next(1, 100)});
    } else if (mode == 1) {
        C = rnd.next(850, 1000);
        int n = rnd.next(12, 20);
        for (int i = 0; i < n; ++i) {
            int cost = rnd.next(1, 100);
            int gain = rnd.next(1, 100);
            cities.push_back({cost, gain});
        }
    } else if (mode == 2) {
        int baseCost = rnd.next(2, 50);
        int baseGain = rnd.next(2, 50);
        C = rnd.next(baseGain + 1, 1000);
        cities.push_back({baseCost, baseGain});
        cities.push_back({min(100, baseCost + rnd.next(1, 50)),
                          rnd.next(1, baseGain)});
        cities.push_back({rnd.next(1, baseCost), min(100, baseGain + rnd.next(1, 50))});
    } else if (mode == 3) {
        int n = rnd.next(1, 6);
        C = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            cities.push_back({rnd.next(1, 15), rnd.next(1, 30)});
        }
    } else if (mode == 4) {
        C = rnd.next(1, 1000);
        int n = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) {
            int gain = (i % 2 == 0) ? rnd.next(80, 100) : rnd.next(1, 20);
            int cost = rnd.next(1, 100);
            cities.push_back({cost, gain});
        }
    } else {
        C = rnd.next(1, 1000);
        int n = rnd.next(7, 20);
        for (int i = 0; i < n; ++i) {
            int cost = rnd.wnext(100, rnd.next(-2, 2)) + 1;
            int gain = rnd.wnext(100, rnd.next(-2, 2)) + 1;
            cities.push_back({cost, gain});
        }
    }

    shuffle(cities.begin(), cities.end());

    println(C, static_cast<int>(cities.size()));
    for (const auto& city : cities) {
        println(city.first, city.second);
    }

    return 0;
}
