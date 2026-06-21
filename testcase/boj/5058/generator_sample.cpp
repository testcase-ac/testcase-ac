#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Doll = pair<int, int>;

vector<Doll> makeChain(int m) {
    int startW = rnd.next(1, 60);
    int startH = rnd.next(1, 60);
    int stepW = rnd.next(1, 7);
    int stepH = rnd.next(1, 7);

    vector<Doll> dolls;
    for (int i = 0; i < m; ++i) {
        dolls.push_back({startW + i * stepW, startH + i * stepH});
    }
    return dolls;
}

vector<Doll> makeAntichain(int m) {
    int baseW = rnd.next(1, 100);
    int baseH = rnd.next(100, 250);
    int stepW = rnd.next(1, 9);
    int stepH = rnd.next(1, 9);

    vector<Doll> dolls;
    for (int i = 0; i < m; ++i) {
        dolls.push_back({baseW + i * stepW, max(1, baseH - i * stepH)});
    }
    return dolls;
}

vector<Doll> makeEqualDimensionCase(int m) {
    vector<Doll> dolls;
    int fixedW = rnd.next(1, 120);
    int fixedH = rnd.next(1, 120);

    for (int i = 0; i < m; ++i) {
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            dolls.push_back({fixedW, rnd.next(1, 200)});
        } else if (mode == 1) {
            dolls.push_back({rnd.next(1, 200), fixedH});
        } else {
            dolls.push_back({fixedW, fixedH});
        }
    }
    return dolls;
}

vector<Doll> makeClusteredCase(int m) {
    vector<Doll> anchors = {
        {rnd.next(1, 15), rnd.next(1, 15)},
        {rnd.next(16, 40), rnd.next(16, 40)},
        {rnd.next(41, 80), rnd.next(41, 80)},
    };

    vector<Doll> dolls;
    for (int i = 0; i < m; ++i) {
        Doll anchor = rnd.any(anchors);
        int w = min(10000, max(1, anchor.first + rnd.next(-5, 5)));
        int h = min(10000, max(1, anchor.second + rnd.next(-5, 5)));
        dolls.push_back({w, h});
    }
    return dolls;
}

vector<Doll> makeBoundaryCase(int m) {
    vector<Doll> pool = {
        {1, 1},
        {1, 10000},
        {10000, 1},
        {9999, 9999},
        {10000, 10000},
    };

    vector<Doll> dolls;
    for (int i = 0; i < m; ++i) {
        Doll d = rnd.any(pool);
        if (rnd.next(0, 2) == 0) {
            d.first = min(10000, max(1, d.first + rnd.next(-3, 3)));
            d.second = min(10000, max(1, d.second + rnd.next(-3, 3)));
        }
        dolls.push_back(d);
    }
    return dolls;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int m = rnd.next(1, 35);
        if (rnd.next(0, 5) == 0) {
            m = rnd.next(36, 80);
        }

        vector<Doll> dolls;
        if (mode == 0) {
            dolls = makeChain(m);
        } else if (mode == 1) {
            dolls = makeAntichain(m);
        } else if (mode == 2) {
            dolls = makeEqualDimensionCase(m);
        } else if (mode == 3) {
            dolls = makeClusteredCase(m);
        } else {
            dolls = makeBoundaryCase(m);
        }

        shuffle(dolls.begin(), dolls.end());

        println(m);
        for (int i = 0; i < m; ++i) {
            if (i > 0) {
                cout << ' ';
            }
            cout << dolls[i].first << ' ' << dolls[i].second;
        }
        cout << '\n';
    }

    return 0;
}
