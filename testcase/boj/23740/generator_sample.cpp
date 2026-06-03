#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Route {
    long long s;
    long long e;
    long long c;
};

Route makeRoute(long long s, long long e) {
    return {s, e, rnd.next(1LL, 1000000000LL)};
}

void addDisjoint(vector<Route>& routes) {
    int n = rnd.next(1, 18);
    long long cur = rnd.next(0LL, 20LL);
    for (int i = 0; i < n; ++i) {
        long long len = rnd.next(1LL, 8LL);
        routes.push_back(makeRoute(cur, cur + len));
        cur += len + rnd.next(1LL, 7LL);
    }
}

void addTouchingChain(vector<Route>& routes) {
    int n = rnd.next(2, 25);
    long long cur = rnd.next(0LL, 30LL);
    for (int i = 0; i < n; ++i) {
        long long len = rnd.next(1LL, 10LL);
        routes.push_back(makeRoute(cur, cur + len));
        cur += rnd.next(0LL, len);
    }
}

void addNested(vector<Route>& routes) {
    int n = rnd.next(3, 20);
    long long left = rnd.next(0LL, 40LL);
    long long right = left + rnd.next(30LL, 120LL);
    routes.push_back(makeRoute(left, right));
    for (int i = 1; i < n; ++i) {
        long long s = rnd.next(left, right - 1);
        long long e = rnd.next(s + 1, right);
        routes.push_back(makeRoute(s, e));
    }
}

void addMixedClusters(vector<Route>& routes) {
    int clusters = rnd.next(2, 5);
    long long base = rnd.next(0LL, 20LL);
    for (int g = 0; g < clusters; ++g) {
        int count = rnd.next(2, 8);
        long long width = rnd.next(5LL, 25LL);
        for (int i = 0; i < count; ++i) {
            long long s = base + rnd.next(0LL, width - 1);
            long long e = base + rnd.next(s - base + 1, width + 8);
            routes.push_back(makeRoute(s, e));
        }
        base += width + rnd.next(0LL, 12LL);
    }
}

void addBoundary(vector<Route>& routes) {
    int n = rnd.next(2, 14);
    long long base = 1000000000LL - rnd.next(30LL, 200LL);
    routes.push_back(makeRoute(0, rnd.next(1LL, 20LL)));
    routes.push_back(makeRoute(999999999LL, 1000000000LL));
    for (int i = 2; i < n; ++i) {
        long long s = rnd.next(base, 999999999LL);
        long long e = rnd.next(s + 1, 1000000000LL);
        routes.push_back(makeRoute(s, e));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Route> routes;
    int mode = rnd.next(0, 4);
    if (mode == 0) addDisjoint(routes);
    if (mode == 1) addTouchingChain(routes);
    if (mode == 2) addNested(routes);
    if (mode == 3) addMixedClusters(routes);
    if (mode == 4) addBoundary(routes);

    shuffle(routes.begin(), routes.end());

    println((int)routes.size());
    for (const Route& route : routes) {
        println(route.s, route.e, route.c);
    }

    return 0;
}
