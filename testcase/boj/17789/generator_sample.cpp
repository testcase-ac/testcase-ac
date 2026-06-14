#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampDiameter(int x) {
    return max(1, min(10000, x));
}

pair<int, int> pedestalFor(int diameter, int style) {
    int d = clampDiameter(diameter);
    if (style == 0 || d == 10000) {
        return {d, d};
    }
    if (style == 1 || d == 1) {
        return {d, d + 1};
    }
    return {d, d - 1};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<pair<int, int>> pedestals;
    vector<int> vases;

    if (mode == 0) {
        int p = rnd.next(0, 4);
        int base = rnd.next(1, 9996);
        for (int i = 0; i < p; ++i) {
            pedestals.push_back(pedestalFor(base + i, rnd.next(0, 2)));
        }
        if (rnd.next(0, 1) == 0) {
            vases.clear();
        } else {
            vases.push_back(clampDiameter(base + p + 3));
        }
    } else if (mode == 1) {
        int n = rnd.next(1, 8);
        int base = rnd.next(1, 9992);
        for (int i = 0; i < n; ++i) {
            int d = base + rnd.next(0, 5);
            pedestals.push_back(pedestalFor(d, 0));
            vases.push_back(d);
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 9);
        int base = rnd.next(2, 9992);
        for (int i = 0; i < n; ++i) {
            int d = base + rnd.next(0, 5);
            pedestals.push_back(pedestalFor(d, rnd.next(1, 2)));
            vases.push_back(d);
        }
    } else if (mode == 3) {
        int p = rnd.next(3, 10);
        int base = rnd.next(2, 9990);
        for (int i = 0; i < p; ++i) {
            int d = base + rnd.next(0, 3);
            pedestals.push_back(pedestalFor(d, rnd.next(0, 2)));
        }
        int demand = base + rnd.next(0, 3);
        int v = rnd.next(p + 1, p + 3);
        for (int i = 0; i < v; ++i) {
            vases.push_back(demand);
        }
    } else if (mode == 4) {
        int p = rnd.next(4, 12);
        int base = rnd.next(1, 9990);
        for (int i = 0; i < p; ++i) {
            int d = base + rnd.next(0, 6);
            pedestals.push_back(pedestalFor(d, rnd.next(0, 2)));
        }
        int v = rnd.next(1, p);
        for (int i = 0; i < v; ++i) {
            int d = base + rnd.next(0, 6);
            if (rnd.next(0, 4) == 0) {
                d += rnd.next(7, 9);
            }
            vases.push_back(clampDiameter(d));
        }
    } else if (mode == 5) {
        int p = rnd.next(2, 8);
        vector<int> choices = {1, 2, 9999, 10000};
        for (int i = 0; i < p; ++i) {
            int d = rnd.any(choices);
            pedestals.push_back(pedestalFor(d, rnd.next(0, 2)));
        }
        int v = rnd.next(1, p + 1);
        for (int i = 0; i < v; ++i) {
            vases.push_back(rnd.any(choices));
        }
    } else {
        int p = rnd.next(8, 18);
        int base = rnd.next(2, 9980);
        for (int i = 0; i < p; ++i) {
            int d = base + rnd.next(0, 12);
            pedestals.push_back(pedestalFor(d, rnd.next(0, 2)));
        }
        int v = rnd.next(1, min(p + 4, 20));
        for (int i = 0; i < v; ++i) {
            vases.push_back(clampDiameter(base + rnd.next(0, 14)));
        }
    }

    shuffle(pedestals.begin(), pedestals.end());
    shuffle(vases.begin(), vases.end());

    println(static_cast<int>(pedestals.size()), static_cast<int>(vases.size()));
    for (const auto& pedestal : pedestals) {
        if (rnd.next(0, 1) == 0) {
            println(pedestal.first, pedestal.second);
        } else {
            println(pedestal.second, pedestal.first);
        }
    }
    println(vases);

    return 0;
}
