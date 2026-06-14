#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static vector<int> unstableCandidates(int n, int m) {
    vector<int> candidates;
    for (int x = 0; x < n; ++x) {
        if (x != 0 && x != m) candidates.push_back(x);
    }
    return candidates;
}

static vector<int> chooseUnstable(int n, int m, int wanted) {
    vector<int> candidates = unstableCandidates(n, m);
    shuffle(candidates.begin(), candidates.end());
    wanted = min(wanted, (int)candidates.size());
    candidates.resize(wanted);
    sort(candidates.begin(), candidates.end());
    return candidates;
}

static int randomMove(int n) {
    if (n == 1) return 0;
    return rnd.next(0, n - 1);
}

static void printCase(int n, int m, const vector<pair<int, int>>& moves,
                      const vector<int>& unstable) {
    println(n, m, (int)moves.size());
    for (auto [g, y] : moves) println(g, y);
    println((int)unstable.size());
    for (int x : unstable) println(x);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    int m = 0;
    int k = 1;
    vector<pair<int, int>> moves;
    vector<int> unstable;

    if (mode == 0) {
        n = 1;
        m = 0;
        k = rnd.next(1, 12);
        moves.assign(k, {0, 0});
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(0, n - 1);
        k = rnd.next(1, 14);
        for (int i = 0; i < k; ++i) {
            moves.push_back({randomMove(n), randomMove(n)});
        }
        unstable = chooseUnstable(n, m, rnd.next(0, max(0, n - 2)));
    } else if (mode == 2) {
        n = rnd.next(2, 15);
        m = rnd.next(0, n - 1);
        k = rnd.next(3, 25);
        for (int i = 0; i < k; ++i) {
            int g = rnd.next(0, 3) == 0 ? 0 : randomMove(n);
            int y = rnd.next(0, 2) == 0 ? g : randomMove(n);
            moves.push_back({g, y});
        }
        unstable = chooseUnstable(n, m, rnd.next(0, min(n - 2, 4)));
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        m = rnd.next(1, n - 1);
        k = rnd.next(2, 30);
        int cur = m;
        for (int i = 0; i < k; ++i) {
            int target = (i == k - 1) ? 0 : rnd.next(0, n - 1);
            int forced = (target - cur + n) % n;
            int other = randomMove(n);
            if (rnd.next(0, 1) == 0) {
                moves.push_back({forced, other});
            } else {
                moves.push_back({other, forced});
            }
            cur = target;
        }
        unstable = chooseUnstable(n, m, rnd.next(0, min(n - 2, 5)));
    } else if (mode == 4) {
        n = rnd.next(4, 30);
        m = rnd.next(1, n - 1);
        k = rnd.next(5, 45);
        for (int i = 0; i < k; ++i) {
            int base = rnd.next(0, n - 1);
            moves.push_back({base, rnd.next(0, 3) == 0 ? base : randomMove(n)});
        }
        unstable = chooseUnstable(n, m, rnd.next(max(0, n / 3), n - 2));
    } else if (mode == 5) {
        n = rnd.next(30, 120);
        m = rnd.next(0, n - 1);
        k = rnd.next(40, 180);
        for (int i = 0; i < k; ++i) {
            int g = rnd.next(0, 4) == 0 ? 0 : randomMove(n);
            int y = rnd.next(0, 4) == 0 ? (n - g) % n : randomMove(n);
            moves.push_back({g, y});
        }
        unstable = chooseUnstable(n, m, rnd.next(0, min(n - 2, 20)));
    } else {
        n = 3000;
        m = rnd.next(0, n - 1);
        k = rnd.next(500, 3000);
        for (int i = 0; i < k; ++i) {
            int g = rnd.next(0, 6) == 0 ? 0 : rnd.next(0, n - 1);
            int y = rnd.next(0, 6) == 0 ? g : rnd.next(0, n - 1);
            moves.push_back({g, y});
        }
        unstable = chooseUnstable(n, m, rnd.next(0, 80));
    }

    printCase(n, m, moves, unstable);
    return 0;
}
