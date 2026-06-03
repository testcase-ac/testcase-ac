#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

struct Route {
    long long cost;
    vector<int> cities;
};

vector<int> uniqueRoute(int cityLimit, int len) {
    vector<int> cities(cityLimit);
    iota(cities.begin(), cities.end(), 1);
    shuffle(cities.begin(), cities.end());
    cities.resize(len);
    return cities;
}

vector<int> routeThrough(int cityLimit, const vector<int>& fixed) {
    vector<int> route = fixed;
    int targetLen = rnd.next(static_cast<int>(fixed.size()), min(8, cityLimit));
    vector<int> extra;
    for (int city = 1; city <= cityLimit; ++city) {
        if (find(fixed.begin(), fixed.end(), city) == fixed.end()) {
            extra.push_back(city);
        }
    }
    shuffle(extra.begin(), extra.end());
    for (int i = 0; static_cast<int>(route.size()) < targetLen; ++i) {
        route.push_back(extra[i]);
    }
    return route;
}

vector<int> routeFromTo(int cityLimit, int from, int to, int len) {
    vector<int> route = {from};
    vector<int> middle;
    for (int city = 1; city <= cityLimit; ++city) {
        if (city != from && city != to) {
            middle.push_back(city);
        }
    }
    shuffle(middle.begin(), middle.end());
    for (int i = 0; static_cast<int>(route.size()) + 1 < len; ++i) {
        route.push_back(middle[i]);
    }
    route.push_back(to);
    return route;
}

void appendRandomRoutes(vector<Route>& routes, int count, int cityLimit, int minCost, int maxCost) {
    for (int i = 0; i < count; ++i) {
        int len = rnd.next(2, min(8, cityLimit));
        routes.push_back({rnd.next(minCost, maxCost), uniqueRoute(cityLimit, len)});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cityLimit = rnd.next(6, 18);
    int mode = rnd.next(5);
    int a = rnd.next(1, cityLimit);
    int b = rnd.next(1, cityLimit - 1);
    if (b >= a) ++b;

    vector<Route> routes;

    if (mode == 0) {
        vector<int> route = routeThrough(cityLimit, {a, b});
        routes.push_back({rnd.next(1, 30), route});
        appendRandomRoutes(routes, rnd.next(1, 8), cityLimit, 1, 80);
    } else if (mode == 1) {
        int mid = rnd.next(1, cityLimit - 2);
        if (mid >= min(a, b)) ++mid;
        if (mid >= max(a, b)) ++mid;
        routes.push_back({rnd.next(1, 20), {a, mid}});
        routes.push_back({rnd.next(1, 20), {mid, b}});
        appendRandomRoutes(routes, rnd.next(0, 8), cityLimit, 1, 100);
    } else if (mode == 2) {
        int steps = rnd.next(3, min(6, cityLimit));
        vector<int> chain = routeFromTo(cityLimit, a, b, steps);
        for (int i = 0; i + 1 < steps; ++i) {
            routes.push_back({rnd.next(1, 25), {chain[i], chain[i + 1]}});
        }
        appendRandomRoutes(routes, rnd.next(2, 8), cityLimit, 10, 120);
    } else if (mode == 3) {
        int split = max(2, cityLimit / 2);
        a = rnd.next(1, split);
        b = rnd.next(split + 1, cityLimit);
        for (int i = 0; i < rnd.next(3, 10); ++i) {
            int sideLo = rnd.next(2) == 0 ? 1 : split + 1;
            int sideHi = sideLo == 1 ? split : cityLimit;
            int len = rnd.next(2, min(6, sideHi - sideLo + 1));
            vector<int> pool;
            for (int city = sideLo; city <= sideHi; ++city) pool.push_back(city);
            shuffle(pool.begin(), pool.end());
            pool.resize(len);
            routes.push_back({rnd.next(1, 90), pool});
        }
    } else {
        int mid1 = rnd.next(1, cityLimit - 2);
        if (mid1 >= min(a, b)) ++mid1;
        if (mid1 >= max(a, b)) ++mid1;
        int mid2 = rnd.next(1, cityLimit - 3);
        vector<int> forbidden = {a, b, mid1};
        sort(forbidden.begin(), forbidden.end());
        for (int city : forbidden) {
            if (mid2 >= city) ++mid2;
        }
        long long baseCost = rnd.next(5, 40);
        routes.push_back({baseCost, {a, mid1, b}});
        routes.push_back({baseCost, {a, mid2, b}});
        routes.push_back({rnd.next(1, 20), {a, mid1}});
        routes.push_back({rnd.next(1, 20), {mid2, b}});
        appendRandomRoutes(routes, rnd.next(1, 6), cityLimit, 1, 100);
    }

    shuffle(routes.begin(), routes.end());

    println(a, b, static_cast<int>(routes.size()));
    for (const Route& route : routes) {
        println(route.cost, static_cast<int>(route.cities.size()));
        println(route.cities);
    }

    return 0;
}
