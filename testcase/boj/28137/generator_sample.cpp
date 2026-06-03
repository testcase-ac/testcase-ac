#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

const ll LIM = 1000000000LL;

bool inRange(ll v) {
    return -LIM <= v && v <= LIM;
}

bool addPoint(vector<pair<ll, ll>>& points, set<pair<ll, ll>>& used, ll x, ll y) {
    if (!inRange(x) || !inRange(y)) return false;
    if (!used.insert({x, y}).second) return false;
    points.push_back({x, y});
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    ll k;
    if (mode == 0) {
        vector<ll> special = {-1000000000LL, -2, -1, 0, 1, 2, 1000000000LL};
        k = rnd.any(special);
    } else {
        k = rnd.next(-20, 20);
    }

    int n = rnd.next(2, 18);
    vector<pair<ll, ll>> points;
    set<pair<ll, ll>> used;

    int groups = rnd.next(1, min(5, n));
    int remaining = n;
    for (int g = 0; g < groups && remaining > 0; ++g) {
        int groupSize = (g + 1 == groups) ? remaining : rnd.next(1, remaining - (groups - g - 1));
        remaining -= groupSize;

        ll b = rnd.next(-30, 30);
        vector<ll> xs;
        int tries = 0;
        while ((int)xs.size() < groupSize && tries++ < 1000) {
            ll x;
            if (abs(k) > 1000000) {
                x = rnd.next(-1, 1);
            } else if (abs(k) > 1000) {
                x = rnd.next(-1000, 1000);
            } else {
                x = rnd.next(-30, 30);
            }

            ll y = k * x + b;
            if (find(xs.begin(), xs.end(), x) == xs.end() && addPoint(points, used, x, y)) {
                xs.push_back(x);
            }
        }
    }

    while ((int)points.size() < n) {
        ll x = rnd.next(-50, 50);
        ll y = rnd.next(-50, 50);
        addPoint(points, used, x, y);
    }

    shuffle(points.begin(), points.end());

    println(n, k);
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}
