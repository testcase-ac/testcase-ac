#include "testlib.h"
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

static vector<pair<int, int>> makeCase(int n, int mode) {
    vector<pair<int, int>> stations(n);

    if (mode == 0) {
        int surplus = 0;
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, 12);
            int g = d + rnd.next(0, 5);
            stations[i] = {g, d};
            surplus += g - d;
        }
        int drain = rnd.next(0, min(surplus, stations[0].first));
        stations[0].first -= drain;
        return stations;
    }

    if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(2, 20);
            int g = rnd.next(0, d - 1);
            stations[i] = {g, d};
        }
        return stations;
    }

    if (mode == 2) {
        int targetStart = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            stations[i] = {rnd.next(0, 3), rnd.next(3, 9)};
        }
        stations[targetStart] = {rnd.next(30, 80), rnd.next(1, 5)};
        stations[(targetStart + n - 1) % n].first = rnd.next(0, 1);
        stations[(targetStart + n - 1) % n].second = rnd.next(10, 20);
        return stations;
    }

    if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int d = rnd.any(vector<int>{1, 2, 511, 512});
            int g = rnd.any(vector<int>{0, 1, 511, 512});
            stations[i] = {g, d};
        }
        return stations;
    }

    int balance = 0;
    for (int i = 0; i < n; ++i) {
        int d = rnd.next(1, 15);
        int delta = rnd.next(-5, 5);
        int g = max(0, min(512, d + delta));
        stations[i] = {g, d};
        balance += g - d;
    }
    if (balance < 0) {
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end());
        for (int idx : order) {
            int add = min(512 - stations[idx].first, -balance);
            stations[idx].first += add;
            balance += add;
            if (balance >= 0) break;
        }
    }
    return stations;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 6);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(3, 18);
        int mode = rnd.next(0, 4);
        vector<pair<int, int>> stations = makeCase(n, mode);

        println(n);
        for (auto [g, d] : stations) {
            println(g, d);
        }
    }

    return 0;
}
