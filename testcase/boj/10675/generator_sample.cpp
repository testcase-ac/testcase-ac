#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

struct Route {
    int cost;
    vector<int> cities;
};

static int freshCity(set<int>& used) {
    int city = rnd.next(1, 10000);
    while (used.count(city)) {
        city = rnd.next(1, 10000);
    }
    used.insert(city);
    return city;
}

static Route makeRoute(int cost, const vector<int>& required, int extraCount,
                       set<int>& used) {
    vector<int> extras;
    for (int i = 0; i < extraCount; ++i) {
        extras.push_back(freshCity(used));
    }
    shuffle(extras.begin(), extras.end());

    vector<vector<int>> gaps(required.size() + 1);
    for (int city : extras) {
        gaps[rnd.next((int)gaps.size())].push_back(city);
    }

    vector<int> cities;
    for (int i = 0; i < (int)required.size(); ++i) {
        cities.insert(cities.end(), gaps[i].begin(), gaps[i].end());
        cities.push_back(required[i]);
    }
    cities.insert(cities.end(), gaps.back().begin(), gaps.back().end());
    return {cost, cities};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<int> used;
    int a = freshCity(used);
    int b = rnd.next(0, 7) == 0 ? a : freshCity(used);
    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 9);

    vector<Route> routes;
    if (mode == 0 || a == b) {
        vector<int> direct = {a};
        if (a != b) {
            direct.push_back(freshCity(used));
            direct.push_back(b);
        } else {
            direct.push_back(freshCity(used));
        }
        routes.push_back(makeRoute(rnd.next(1, 30), direct, rnd.next(0, 3), used));
    } else if (mode == 1) {
        routes.push_back(makeRoute(rnd.next(1, 30), {b, a}, rnd.next(0, 3), used));
    } else if (mode == 2) {
        routes.push_back(makeRoute(rnd.next(1, 30), {a, freshCity(used)}, rnd.next(0, 3), used));
    } else {
        routes.push_back(makeRoute(rnd.next(1, 30), {freshCity(used), b}, rnd.next(0, 3), used));
    }

    if (a != b && rnd.next(0, 1) == 1) {
        int expensive = rnd.next(50, 1000);
        routes.push_back(makeRoute(expensive, {a, b}, rnd.next(0, 4), used));
    }

    while ((int)routes.size() < n) {
        int kind = rnd.next(0, 3);
        int len = rnd.next(2, 8);
        vector<int> cities;
        if (kind == 0) {
            cities.push_back(a);
        } else if (kind == 1) {
            cities.push_back(b);
        } else if (kind == 2 && a != b) {
            cities.push_back(b);
            cities.push_back(a);
        }
        while ((int)cities.size() < len) {
            cities.push_back(freshCity(used));
        }
        routes.push_back(makeRoute(rnd.next(1, 1000), cities, 0, used));
    }

    shuffle(routes.begin(), routes.end());

    println(a, b, (int)routes.size());
    for (const Route& route : routes) {
        println(route.cost, (int)route.cities.size());
        println(route.cities);
    }

    return 0;
}
