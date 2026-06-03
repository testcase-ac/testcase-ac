#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Route {
    int cost;
    vector<int> cities;
};

static vector<int> shuffledPool(int limit, const vector<int>& skipped) {
    vector<int> pool;
    for (int city = 1; city <= limit; ++city) {
        if (find(skipped.begin(), skipped.end(), city) == skipped.end()) {
            pool.push_back(city);
        }
    }
    shuffle(pool.begin(), pool.end());
    return pool;
}

static vector<int> uniqueRoute(vector<int> required, int poolLimit, int minLength) {
    vector<int> pool = shuffledPool(poolLimit, required);
    int targetLength = rnd.next(max<int>(minLength, required.size()), min(8, poolLimit));
    for (int city : pool) {
        if ((int)required.size() == targetLength) {
            break;
        }
        required.push_back(city);
    }
    return required;
}

static void printInput(int a, int b, vector<Route> routes) {
    shuffle(routes.begin(), routes.end());
    println(a, b, (int)routes.size());
    for (const Route& route : routes) {
        println(route.cost, (int)route.cities.size());
        println(route.cities);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int poolLimit = rnd.next(8, 20);
    int a = rnd.next(1, poolLimit);
    int b = rnd.next(1, poolLimit);
    if (mode != 4) {
        while (b == a) {
            b = rnd.next(1, poolLimit);
        }
    }

    vector<Route> routes;
    int routeCount = rnd.next(1, 8);

    if (mode == 0) {
        vector<int> direct;
        if (rnd.next(0, 1) == 0) {
            direct = uniqueRoute({a, b}, poolLimit, 2);
        } else {
            int middle = rnd.next(1, poolLimit);
            while (middle == a || middle == b) {
                middle = rnd.next(1, poolLimit);
            }
            direct = uniqueRoute({a, middle, b}, poolLimit, 3);
        }
        routes.push_back({rnd.next(1, 30), direct});
    } else if (mode == 1) {
        int transfer = rnd.next(1, poolLimit);
        while (transfer == a || transfer == b) {
            transfer = rnd.next(1, poolLimit);
        }
        routes.push_back({rnd.next(1, 40), uniqueRoute({a, transfer}, poolLimit, 2)});
        routes.push_back({rnd.next(1, 40), uniqueRoute({transfer, b}, poolLimit, 2)});
    } else if (mode == 2) {
        routes.push_back({rnd.next(1, 40), uniqueRoute({b, a}, poolLimit, 2)});
    } else if (mode == 3) {
        int x = rnd.next(1, poolLimit);
        int y = rnd.next(1, poolLimit);
        while (x == a || x == b) {
            x = rnd.next(1, poolLimit);
        }
        while (y == a || y == b || y == x) {
            y = rnd.next(1, poolLimit);
        }
        routes.push_back({rnd.next(1, 40), uniqueRoute({a, x}, poolLimit, 2)});
        routes.push_back({rnd.next(1, 40), uniqueRoute({y, b}, poolLimit, 2)});
    } else {
        b = a;
        int x = rnd.next(1, poolLimit);
        int y = rnd.next(1, poolLimit);
        while (y == x) {
            y = rnd.next(1, poolLimit);
        }
        routes.push_back({rnd.next(1, 40), uniqueRoute({x, y}, poolLimit, 2)});
    }

    while ((int)routes.size() < routeCount) {
        vector<int> route;
        int len = rnd.next(2, 7);
        vector<int> pool;
        for (int city = 1; city <= poolLimit; ++city) {
            pool.push_back(city);
        }
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < len; ++i) {
            route.push_back(pool[i]);
        }
        routes.push_back({rnd.next(1, 80), route});
    }

    printInput(a, b, routes);
    return 0;
}
