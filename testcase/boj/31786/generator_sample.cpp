#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;
using Query = vector<ll>;

const ll COORD_MIN = -1000000000LL;
const ll COORD_MAX = 1000000000LL;

ll nonzeroCoord(ll lo, ll hi) {
    ll value = rnd.next(lo, hi);
    if (value != 0) return value;
    return rnd.next(0, 1) == 0 ? -1 : 1;
}

void addAsk(vector<Query>& queries, ll x) {
    queries.push_back({1, x});
}

void addToggle(vector<Query>& queries, ll x, ll y) {
    queries.push_back({2, x, y});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Query> queries;
    int mode = rnd.next(0, 4);
    int smallX = rnd.next(1, 10);

    if (mode == 0) {
        int q = rnd.next(1, 8);
        for (int i = 0; i < q; ++i) {
            addAsk(queries, rnd.next(1, 20));
        }
    } else if (mode == 1) {
        int stations = rnd.next(2, 8);
        for (int i = 0; i < stations; ++i) {
            ll y = nonzeroCoord(-12, 12);
            addToggle(queries, rnd.next(-4, 4), y);
        }
        for (int i = 0; i < rnd.next(2, 5); ++i) {
            addAsk(queries, rnd.next(1, 12));
        }
    } else if (mode == 2) {
        vector<pair<ll, ll>> points = {
            {COORD_MIN, COORD_MIN},
            {COORD_MAX, COORD_MAX},
            {-COORD_MAX, 1},
            {COORD_MAX, -1},
        };
        shuffle(points.begin(), points.end());
        int count = rnd.next(2, (int)points.size());
        for (int i = 0; i < count; ++i) {
            addToggle(queries, points[i].first, points[i].second);
        }
        addAsk(queries, COORD_MAX);
        addAsk(queries, rnd.next(1, 5));
    } else if (mode == 3) {
        int pairs = rnd.next(1, 4);
        for (int i = 0; i < pairs; ++i) {
            ll x = rnd.next(-8, 8);
            ll y = nonzeroCoord(-8, 8);
            addToggle(queries, x, y);
            if (rnd.next(0, 1)) addAsk(queries, rnd.next(1, 10));
            addToggle(queries, x, y);
            if (rnd.next(0, 1)) addToggle(queries, x, -y);
        }
        addAsk(queries, rnd.next(1, 10));
    } else {
        int radius = rnd.next(2, 20);
        int stations = rnd.next(4, 10);
        for (int i = 0; i < stations; ++i) {
            ll x = rnd.next(-radius, radius);
            ll y;
            if (rnd.next(0, 1) == 0) {
                y = nonzeroCoord(-radius, radius);
            } else {
                y = rnd.next(0, 1) == 0 ? -radius : radius;
            }
            addToggle(queries, x, y);
        }
        addAsk(queries, max(1, radius - rnd.next(0, 2)));
        addAsk(queries, radius);
        addAsk(queries, radius + rnd.next(1, 3));
    }

    if (rnd.next(0, 2) == 0) {
        addToggle(queries, -smallX, smallX);
        addAsk(queries, smallX);
    }

    println((int)queries.size());
    for (const Query& query : queries) {
        println(query);
    }

    return 0;
}
