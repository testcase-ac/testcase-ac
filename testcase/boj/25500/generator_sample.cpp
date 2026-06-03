#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct City {
    int x;
    int y;
    int z;
};

int boundedValue(int base, int spread) {
    return max(0, min(1000000000, base + rnd.next(-spread, spread)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    int k = rnd.next(1, 30);
    vector<City> cities;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1, 10);
        int x = rnd.next(0, 20);
        int y = rnd.next(0, 20);
        int z = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            cities.push_back({x, y, z});
        }
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        k = rnd.next(2, 25);
        int y = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            int x = i * rnd.next(1, 5);
            int z = rnd.next(0, 5 * k);
            cities.push_back({x, y + rnd.next(0, 1), z});
        }
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        k = rnd.next(2, 25);
        int x = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            int y = i * rnd.next(1, 6);
            int z = rnd.next(0, 5 * k);
            cities.push_back({x + rnd.next(0, 1), y, z});
        }
    } else if (mode == 3) {
        n = rnd.next(4, 14);
        k = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            int rem = (i % 2 == 0) ? rnd.next(0, k - 1) : (k - cities.back().z % k) % k;
            int z = rem + k * rnd.next(0, 4);
            cities.push_back({rnd.next(0, 80), rnd.next(0, 80), z});
        }
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        k = rnd.any(vector<int>{1, 2, 199999, 200000});
        for (int i = 0; i < n; ++i) {
            int base = (i % 2 == 0) ? 0 : 1000000000;
            cities.push_back({
                boundedValue(base, 20),
                boundedValue(1000000000 - base, 20),
                boundedValue(base, 20),
            });
        }
    } else {
        n = rnd.next(2, 14);
        k = rnd.next(1, 40);
        int maxCoord = rnd.any(vector<int>{5, 20, 100, 1000000000});
        for (int i = 0; i < n; ++i) {
            cities.push_back({
                rnd.next(0, maxCoord),
                rnd.next(0, maxCoord),
                rnd.next(0, maxCoord),
            });
        }
    }

    shuffle(cities.begin(), cities.end());

    println(n, k);
    for (const City& city : cities) {
        println(city.x, city.y, city.z);
    }

    return 0;
}
