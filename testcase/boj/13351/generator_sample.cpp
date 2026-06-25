#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

static vector<int> identityPermutation(int s) {
    vector<int> p(s);
    for (int i = 0; i < s; ++i) {
        p[i] = i + 1;
    }
    return p;
}

static int cappedPermutationCount(int s) {
    int count = 1;
    for (int i = 2; i <= s && count < 100; ++i) {
        count *= i;
    }
    return min(count, 100);
}

static void addIfNew(vector<vector<int>>& preferences, set<vector<int>>& seen,
                     const vector<int>& p, int limit) {
    if ((int)preferences.size() < limit && seen.insert(p).second) {
        preferences.push_back(p);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int s;
    int m;

    if (mode == 0) {
        s = rnd.next(1, 4);
        m = rnd.next(1, min(8, s == 1 ? 1 : s * (s - 1)));
    } else if (mode == 1) {
        s = rnd.next(3, 10);
        m = rnd.next(2, min(10, s));
    } else if (mode == 2) {
        s = rnd.next(5, 14);
        m = rnd.next(3, min(16, s * 2));
    } else if (mode == 3) {
        s = rnd.next(8, 24);
        m = rnd.next(2, min(20, s + 4));
    } else {
        s = rnd.next(2, 12);
        m = rnd.next(1, min(24, s * s));
    }
    m = min(m, cappedPermutationCount(s));

    vector<vector<int>> preferences;
    set<vector<int>> seen;
    vector<int> base = identityPermutation(s);

    if (mode == 0) {
        do {
            addIfNew(preferences, seen, base, m);
        } while ((int)preferences.size() < m && next_permutation(base.begin(), base.end()));
    } else if (mode == 1) {
        for (int shift = 0; shift < s && (int)preferences.size() < m; ++shift) {
            vector<int> p;
            for (int i = 0; i < s; ++i) {
                p.push_back((i + shift) % s + 1);
            }
            if (rnd.next(0, 1)) {
                reverse(p.begin() + max(1, s / 2), p.end());
            }
            addIfNew(preferences, seen, p, m);
        }
    } else if (mode == 2) {
        int prefix = rnd.next(2, min(5, s));
        vector<int> favoritePool = base;
        shuffle(favoritePool.begin(), favoritePool.end());
        favoritePool.resize(prefix);

        for (int i = 0; i < m * 4 && (int)preferences.size() < m; ++i) {
            vector<int> p = favoritePool;
            shuffle(p.begin(), p.end());
            for (int song = 1; song <= s; ++song) {
                if (find(p.begin(), p.end(), song) == p.end()) {
                    p.push_back(song);
                }
            }
            shuffle(p.begin() + prefix, p.end());
            addIfNew(preferences, seen, p, m);
        }
    } else if (mode == 3) {
        for (int i = 0; i < m * 5 && (int)preferences.size() < m; ++i) {
            vector<int> p = base;
            int swaps = rnd.next(1, s);
            for (int j = 0; j < swaps; ++j) {
                swap(p[rnd.next(s)], p[rnd.next(s)]);
            }
            addIfNew(preferences, seen, p, m);
        }
    }

    while ((int)preferences.size() < m) {
        vector<int> p = base;
        shuffle(p.begin(), p.end());
        addIfNew(preferences, seen, p, m);
    }

    shuffle(preferences.begin(), preferences.end());

    println(m, s);
    for (const vector<int>& p : preferences) {
        println(p);
    }

    return 0;
}
