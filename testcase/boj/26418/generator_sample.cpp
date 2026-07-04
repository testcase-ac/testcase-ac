#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Ant {
    int position;
    int direction;
};

static vector<int> makePositions(int n, int l, int mode) {
    set<int> used;
    vector<int> positions;

    auto add = [&](int x) {
        if (1 <= x && x < l && used.insert(x).second) {
            positions.push_back(x);
        }
    };

    if (mode == 0) {
        int start = rnd.next(1, min(l - 1, 8));
        int step = rnd.next(1, max(1, (l - start - 1) / max(1, n)));
        for (int i = 0; i < n; ++i) add(start + i * step);
    } else if (mode == 1) {
        int pairs = n / 2;
        for (int i = 0; i < pairs; ++i) {
            int x = rnd.next(1, l / 2);
            add(x);
            add(l - x);
        }
    } else if (mode == 2) {
        int center = l <= 3 ? 1 : rnd.next(2, l - 2);
        add(center);
        for (int d = 1; (int)positions.size() < n && d < l; ++d) {
            if (rnd.next(0, 1) == 0) {
                add(center - d);
                add(center + d);
            } else {
                add(center + d);
                add(center - d);
            }
        }
    } else if (mode == 3) {
        int leftCount = rnd.next(1, n);
        for (int i = 0; i < leftCount; ++i) add(rnd.next(1, min(l - 1, 12)));
        for (int i = leftCount; i < n; ++i) add(rnd.next(max(1, l - 12), l - 1));
    }

    while ((int)positions.size() < n) {
        add(rnd.next(1, l - 1));
    }

    shuffle(positions.begin(), positions.end());
    positions.resize(n);
    return positions;
}

static vector<Ant> makeCase() {
    int mode = rnd.next(0, 5);
    int n;
    int l;

    if (mode == 4) {
        n = rnd.next(40, 90);
        l = rnd.next(n + 1, 250);
    } else {
        n = rnd.next(1, 14);
        l = rnd.next(n + 1, 60);
    }

    vector<int> positions = makePositions(n, l, mode);
    vector<Ant> ants;
    ants.reserve(n);

    int directionMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        int direction;
        if (directionMode == 0) {
            direction = i % 2;
        } else if (directionMode == 1) {
            direction = positions[i] * 2 < l ? 1 : 0;
        } else if (directionMode == 2) {
            direction = positions[i] * 2 < l ? 0 : 1;
        } else {
            direction = rnd.next(0, 1);
        }
        ants.push_back({positions[i], direction});
    }

    shuffle(ants.begin(), ants.end());
    return ants;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        vector<Ant> ants = makeCase();
        int maxPosition = 0;
        for (const Ant& ant : ants) maxPosition = max(maxPosition, ant.position);
        int l = maxPosition + rnd.next(1, 30);
        l = max(l, (int)ants.size() + 1);

        println((int)ants.size(), l);
        for (const Ant& ant : ants) {
            println(ant.position, ant.direction);
        }
    }

    return 0;
}
