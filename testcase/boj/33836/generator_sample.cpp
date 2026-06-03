#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

const ll LIM = 1000000000LL;

ll smallCoord() {
    return rnd.next(-20, 20);
}

ll wideCoord() {
    if (rnd.next(4) == 0) return rnd.any(vector<ll>{-LIM, -LIM + 1, LIM - 1, LIM});
    return rnd.next(-1000000, 1000000);
}

ll coord() {
    return rnd.next(3) == 0 ? wideCoord() : smallCoord();
}

pair<ll, ll> makeQuery() {
    int mode = rnd.next(8);
    if (mode == 0) {
        return {rnd.next(0LL, LIM), 0};
    }
    if (mode == 1) {
        return {rnd.next(-LIM, -1LL), 0};
    }
    if (mode == 2) {
        return {rnd.next(0LL, LIM), rnd.next(1LL, 30LL)};
    }
    if (mode == 3) {
        return {rnd.next(-30LL, -1LL), rnd.next(1LL, 30LL)};
    }
    if (mode == 4) {
        ll y = rnd.next(-30LL, -1LL);
        return {rnd.next(y, 30LL), y};
    }
    if (mode == 5) {
        ll y = rnd.next(-30LL, -1LL);
        return {rnd.next(-30LL, y - 1), y};
    }
    if (mode == 6) {
        return {rnd.any(vector<ll>{-LIM, -1, 0, 1, LIM}), rnd.any(vector<ll>{-LIM, -1, 0, 1, LIM})};
    }
    return {coord(), coord()};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int q = rnd.next(1, 40);
    vector<pair<ll, ll>> queries;
    queries.reserve(q);

    vector<pair<ll, ll>> anchors = {
        {0, 0},
        {1, 0},
        {-1, 0},
        {1, 1},
        {-1, 1},
        {-1, -1},
        {-2, -1},
        {LIM, -LIM},
    };
    shuffle(anchors.begin(), anchors.end());

    for (int i = 0; i < q; ++i) {
        if (i < static_cast<int>(anchors.size()) && rnd.next(3) == 0) {
            queries.push_back(anchors[i]);
        } else {
            queries.push_back(makeQuery());
        }
    }

    println(q);
    for (auto [x, y] : queries) {
        println(x, y);
    }

    return 0;
}
