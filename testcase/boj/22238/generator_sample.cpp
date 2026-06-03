#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const long long COORD_LIMIT = 1000000000LL;
const long long VALUE_LIMIT = 1000000000LL;

pair<long long, long long> normalize(long long x, long long y) {
    long long g = gcd(abs(x), abs(y));
    return {x / g, y / g};
}

pair<long long, long long> randomDirection() {
    vector<pair<long long, long long>> special = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {-1, -1}, {-2, -3}, {3, -2},
    };
    if (rnd.next(100) < 55) return rnd.any(special);

    while (true) {
        long long x = rnd.next(-9, 9);
        long long y = rnd.next(-9, 9);
        if (x == 0 && y == 0) continue;
        return normalize(x, y);
    }
}

pair<long long, long long> missDirection(pair<long long, long long> hitDir) {
    vector<pair<long long, long long>> candidates = {
        {-hitDir.first, -hitDir.second},
        {hitDir.second, -hitDir.first},
        {-hitDir.second, hitDir.first},
        {1, 0},
        {0, 1},
        {-1, 1},
        {2, -1},
    };
    shuffle(candidates.begin(), candidates.end());
    for (auto dir : candidates) {
        if (dir.first == 0 && dir.second == 0) continue;
        if (normalize(dir.first, dir.second) != hitDir) return dir;
    }
    return {-hitDir.first, -hitDir.second};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    pair<long long, long long> dir = randomDirection();

    long long maxComponent = max(abs(dir.first), abs(dir.second));
    long long maxPositionScale = COORD_LIMIT / maxComponent;
    long long scaleCap = min(maxPositionScale, 1000LL);
    if (rnd.next(100) < 15) scaleCap = maxPositionScale;

    set<long long> usedScales;
    vector<long long> positionScales;
    while ((int)positionScales.size() < n) {
        long long scale = rnd.next(1LL, scaleCap);
        if (usedScales.insert(scale).second) positionScales.push_back(scale);
    }
    shuffle(positionScales.begin(), positionScales.end());

    vector<long long> hp;
    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(100);
        if (mode < 25) {
            hp.push_back(rnd.next(1LL, 5LL));
        } else if (mode < 50) {
            hp.push_back(rnd.next(6LL, 30LL));
        } else if (mode < 75) {
            hp.push_back((long long)rnd.any(vector<int>{10, 20, 30, 100}));
        } else {
            hp.push_back(rnd.next(VALUE_LIMIT - 20, VALUE_LIMIT));
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        long long x = dir.first * positionScales[i];
        long long y = dir.second * positionScales[i];
        println(x, y, hp[i]);
    }

    long long accumulatedHitDamage = 0;
    for (int i = 0; i < m; ++i) {
        bool hit = rnd.next(100) < 60;
        pair<long long, long long> attackDir = hit ? dir : missDirection(dir);
        long long attackScale = rnd.next(1LL, min(1000LL, COORD_LIMIT / max(1LL, max(abs(attackDir.first), abs(attackDir.second)))));
        long long damage;
        if (hit && rnd.next(100) < 55) {
            long long target = rnd.any(hp);
            damage = max(1LL, min(VALUE_LIMIT, target - accumulatedHitDamage + rnd.next(-2LL, 2LL)));
            accumulatedHitDamage += damage;
        } else {
            damage = rnd.next(1LL, rnd.next(100) < 20 ? VALUE_LIMIT : 40LL);
            if (hit) accumulatedHitDamage += damage;
        }
        println(attackDir.first * attackScale, attackDir.second * attackScale, damage);
    }

    return 0;
}
