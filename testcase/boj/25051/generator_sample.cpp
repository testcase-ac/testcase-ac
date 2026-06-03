#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

const ll COORD_LIMIT = 1000000000LL;
const ll BEAUTY_LIMIT = 1000000000000LL;
const ll PRICE_LIMIT = 1000000000000000000LL;

struct Star {
    ll x;
    ll y;
    ll s;
};

ll dist2(ll x, ll y) {
    return x * x + y * y;
}

ll clampPrice(ll value) {
    return max(1LL, min(PRICE_LIMIT, value));
}

ll randomBeauty(bool allowLarge) {
    int mode = rnd.next(0, allowLarge ? 4 : 3);
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(1LL, 30LL);
    if (mode == 2) return rnd.next(31LL, 1000LL);
    return rnd.next(BEAUTY_LIMIT - 1000, BEAUTY_LIMIT);
}

void addStar(vector<Star>& stars, set<pair<ll, ll>>& used, ll x, ll y, ll s) {
    if (x == 0 && y == 0) return;
    if (x < -COORD_LIMIT || x > COORD_LIMIT) return;
    if (y < -COORD_LIMIT || y > COORD_LIMIT) return;
    if (!used.insert({x, y}).second) return;
    stars.push_back({x, y, s});
}

void addRandomSmallStar(vector<Star>& stars, set<pair<ll, ll>>& used, bool allowLargeBeauty) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        ll x = rnd.next(-25, 25);
        ll y = rnd.next(-25, 25);
        if (x == 0 && y == 0) continue;
        if (used.count({x, y})) continue;
        addStar(stars, used, x, y, randomBeauty(allowLargeBeauty));
        return;
    }
}

void addRandomLargeStar(vector<Star>& stars, set<pair<ll, ll>>& used) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        ll ax = rnd.next(999999960LL, COORD_LIMIT);
        ll ay = rnd.next(999999960LL, COORD_LIMIT);
        ll x = rnd.next(0, 1) ? ax : -ax;
        ll y = rnd.next(0, 1) ? ay : -ay;
        if (used.count({x, y})) continue;
        addStar(stars, used, x, y, randomBeauty(true));
        return;
    }
}

vector<ll> buildPrices(const vector<Star>& stars) {
    vector<ll> candidates;
    for (const Star& star : stars) {
        ll d = dist2(star.x, star.y);
        candidates.push_back(clampPrice(d));
        candidates.push_back(clampPrice(d - 1));
        candidates.push_back(clampPrice(d + 1));
    }
    candidates.push_back(1);
    candidates.push_back(2);
    candidates.push_back(4);
    candidates.push_back(1000000000000000000LL);
    shuffle(candidates.begin(), candidates.end());

    int m = rnd.next(1, min(8, (int)candidates.size()));
    vector<ll> prices;
    for (ll price : candidates) {
        prices.push_back(price);
        if ((int)prices.size() == m) break;
    }
    shuffle(prices.begin(), prices.end());
    return prices;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Star> stars;
    set<pair<ll, ll>> used;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        vector<pair<ll, ll>> directions = {
            {1, 0}, {0, 1}, {-1, 0}, {0, -1},
            {1, 1}, {-1, 1}, {-1, -1}, {1, -1},
        };
        shuffle(directions.begin(), directions.end());
        int n = rnd.next(1, (int)directions.size());
        for (int i = 0; i < n; ++i) {
            ll scale = rnd.next(1, 8);
            addStar(stars, used, directions[i].first * scale, directions[i].second * scale,
                    randomBeauty(false));
        }
    } else if (mode == 1) {
        vector<pair<ll, ll>> directions = {{1, 0}, {0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}};
        shuffle(directions.begin(), directions.end());
        int rays = rnd.next(1, 3);
        for (int i = 0; i < rays; ++i) {
            int count = rnd.next(1, 4);
            for (int j = 1; j <= count; ++j) {
                addStar(stars, used, directions[i].first * j, directions[i].second * j,
                        randomBeauty(false));
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(4, 14);
        while ((int)stars.size() < n) {
            addRandomSmallStar(stars, used, false);
        }
    } else if (mode == 3) {
        int n = rnd.next(6, 18);
        for (int i = 0; i < n / 2; ++i) {
            ll x = rnd.next(-10, 10);
            ll y = rnd.next(-10, 10);
            if (x == 0 && y == 0) y = 1;
            addStar(stars, used, x, y, randomBeauty(false));
            addStar(stars, used, -y, x, randomBeauty(false));
        }
        while ((int)stars.size() < n) {
            addRandomSmallStar(stars, used, false);
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 10);
        while ((int)stars.size() < n - 1) {
            addRandomSmallStar(stars, used, true);
        }
        addRandomLargeStar(stars, used);
    } else {
        int n = rnd.next(5, 15);
        for (int x = -7; x <= 7 && (int)stars.size() < n; ++x) {
            if (x == 0) continue;
            addStar(stars, used, x, rnd.any(vector<ll>{-1, 1}), randomBeauty(false));
        }
        while ((int)stars.size() < n) {
            addRandomSmallStar(stars, used, false);
        }
    }

    shuffle(stars.begin(), stars.end());
    vector<ll> prices = buildPrices(stars);

    println((int)stars.size(), (int)prices.size());
    for (const Star& star : stars) {
        println(star.x, star.y, star.s);
    }
    println(prices);

    return 0;
}
