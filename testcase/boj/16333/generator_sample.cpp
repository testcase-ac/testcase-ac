#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Wish = pair<int, int>;

static Wish randomWish(int n) {
    int x = rnd.next(1, n);
    int y = rnd.next(1, n - 1);
    if (y >= x) {
        ++y;
    }
    return {x, y};
}

static void addCycle(vector<Wish>& wishes, int n) {
    for (int i = 1; i <= n; ++i) {
        wishes.push_back({i, i == n ? 1 : i + 1});
    }
}

static vector<Wish> makeCase(int n, int m, int mode) {
    vector<Wish> wishes;

    if (mode == 0) {
        addCycle(wishes, n);
        while ((int)wishes.size() < m) {
            wishes.push_back(randomWish(n));
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n && (int)wishes.size() < m; ++i) {
            if (i != center) {
                wishes.push_back({center, i});
            }
        }
        for (int i = 1; i <= n && (int)wishes.size() < m; ++i) {
            if (i != center) {
                wishes.push_back({i, center});
            }
        }
        while ((int)wishes.size() < m) {
            wishes.push_back(randomWish(n));
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        for (int x = 1; x <= split && (int)wishes.size() < m; ++x) {
            for (int y = split + 1; y <= n && (int)wishes.size() < m; ++y) {
                wishes.push_back({x, y});
                if ((int)wishes.size() < m && rnd.next(2) == 0) {
                    wishes.push_back({y, x});
                }
            }
        }
        while ((int)wishes.size() < m) {
            wishes.push_back(randomWish(n));
        }
    } else if (mode == 3) {
        vector<Wish> base;
        int baseSize = rnd.next(1, min(m, max(1, n - 1)));
        while ((int)base.size() < baseSize) {
            base.push_back(randomWish(n));
        }
        while ((int)wishes.size() < m) {
            wishes.push_back(rnd.any(base));
        }
    } else {
        while ((int)wishes.size() < m) {
            int x = rnd.next(1, n);
            int offset = rnd.next(1, n - 1);
            int y = (x + offset - 1) % n + 1;
            wishes.push_back({x, y});
        }
    }

    shuffle(wishes.begin(), wishes.end());
    wishes.resize(m);
    return wishes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    vector<vector<Wish>> cases;
    vector<pair<int, int>> sizes;
    int totalWork = 0;

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0 && rnd.next(4) == 0) {
            n = rnd.next(20, 80);
        } else {
            n = rnd.next(2, 12);
        }

        int mode = rnd.next(0, 4);
        int maxCompactM = min(80, n * max(2, n - 1));
        int m;
        if (mode == 3) {
            m = rnd.next(2, maxCompactM);
        } else {
            m = rnd.next(1, maxCompactM);
        }

        if (totalWork + n + m > 300000) {
            m = max(1, 300000 - totalWork - n);
        }
        totalWork += n + m;

        sizes.push_back({n, m});
        cases.push_back(makeCase(n, m, mode));
    }

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        println(sizes[tc].first, sizes[tc].second);
        for (const Wish& wish : cases[tc]) {
            println(wish.first, wish.second);
        }
    }

    return 0;
}
