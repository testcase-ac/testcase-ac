#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeMostlySolvable(int n, int m) {
    vector<int> forecast;
    vector<int> full(n + 1, 1);
    vector<int> dry;

    while ((int)forecast.size() < m) {
        int remaining = m - (int)forecast.size();
        bool canDrink = !dry.empty();
        bool drink = canDrink && (rnd.next(100) < 38 || remaining <= 2);

        if (drink) {
            int lake = rnd.any(dry);
            forecast.push_back(0);
            full[lake] = 0;
            dry.erase(find(dry.begin(), dry.end(), lake));
        } else {
            int lake = rnd.next(1, n);
            if (full[lake]) {
                forecast.push_back(0);
                full[lake] = 0;
                dry.push_back(lake);
                if ((int)forecast.size() == m) break;
            }
            forecast.push_back(lake);
            full[lake] = 1;
        }
    }

    forecast.resize(m);
    return forecast;
}

vector<int> makeRepeatedLake(int n, int m, bool possible) {
    int lake = rnd.next(1, n);
    vector<int> forecast;

    if (m == 1) {
        forecast.push_back(rnd.next(0, n));
    } else if (possible) {
        forecast.push_back(0);
        forecast.push_back(lake);
        while ((int)forecast.size() + 2 <= m) {
            forecast.push_back(0);
            forecast.push_back(lake);
        }
    } else {
        forecast.push_back(lake);
        forecast.push_back(lake);
    }

    while ((int)forecast.size() < m) {
        if (rnd.next(100) < 45) {
            forecast.push_back(0);
        } else {
            forecast.push_back(rnd.next(1, n));
        }
    }

    forecast.resize(m);
    return forecast;
}

vector<int> makeZeroHeavy(int n, int m) {
    vector<int> forecast;
    int maxLake = rnd.next(1, n);
    for (int i = 0; i < m; ++i) {
        if (rnd.next(100) < 70) {
            forecast.push_back(0);
        } else {
            forecast.push_back(rnd.next(1, maxLake));
        }
    }
    return forecast;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(1, 20);
    println(z);

    int largeInstances = 0;
    for (int tc = 0; tc < z; ++tc) {
        bool makeLarge = largeInstances < 3 && rnd.next(100) < 15;
        int n = makeLarge ? rnd.next(100000, 1000000) : rnd.next(1, 18);
        int m = makeLarge ? rnd.next(1, 80) : rnd.next(1, 50);
        if (n >= 100000 || m >= 100000) ++largeInstances;

        int mode = rnd.next(0, 3);
        vector<int> forecast;
        if (mode == 0) {
            forecast = makeMostlySolvable(n, m);
        } else if (mode == 1) {
            forecast = makeRepeatedLake(n, m, true);
        } else if (mode == 2) {
            forecast = makeRepeatedLake(n, m, false);
        } else {
            forecast = makeZeroHeavy(n, m);
        }

        println(n, m);
        println(forecast);
    }

    return 0;
}
