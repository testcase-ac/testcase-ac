#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

long long randomCost(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(1, 1000);
    if (rnd.next(4) == 0) return 1000000000LL;
    return rnd.next(999999900LL, 1000000000LL);
}

vector<int> chooseCities(int n, int m, int mode) {
    vector<int> cities;

    if (mode == 1) {
        for (int i = 1; i <= n; ++i) cities.push_back(i);
        return cities;
    }

    if (mode == 2) {
        int start = rnd.next(1, n);
        for (int i = 0; i < m; ++i) cities.push_back((start + i - 1) % n + 1);
    } else {
        for (int i = 1; i <= n; ++i) cities.push_back(i);
        shuffle(cities.begin(), cities.end());
        cities.resize(m);
    }

    sort(cities.begin(), cities.end());
    return cities;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 4) {
        n = rnd.next(25, 60);
    } else {
        n = rnd.next(3, 14);
    }

    int m;
    if (mode == 0) {
        m = 1;
    } else if (mode == 1) {
        m = n;
    } else if (mode == 2) {
        m = rnd.next(2, min(n, 6));
    } else {
        m = rnd.next(1, n);
    }

    vector<int> cities = chooseCities(n, m, mode);
    int costMode = rnd.next(3);
    vector<long long> plantCosts(m);
    vector<long long> lineCosts(n);

    for (int i = 0; i < m; ++i) {
        plantCosts[i] = randomCost(costMode);
    }

    for (int i = 0; i < n; ++i) {
        if (mode == 3 && (i == 0 || i + 1 == n)) {
            lineCosts[i] = rnd.next(1, 3);
        } else if (mode == 3 && rnd.next(3) == 0) {
            lineCosts[i] = 1000000000LL;
        } else {
            lineCosts[i] = randomCost(costMode);
        }
    }

    println(n, m);
    for (int i = 0; i < m; ++i) {
        println(cities[i], plantCosts[i]);
    }
    println(lineCosts);

    return 0;
}
