#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    int s;
    int d;
    int f;
    int b;
    vector<int> police;
};

static vector<int> choosePolice(int n, int s, int d, int maxK, const set<int>& preferred) {
    vector<int> candidates;
    vector<int> police;

    for (int x : preferred) {
        if (1 <= x && x <= n && x != s && x != d) {
            police.push_back(x);
        }
    }
    sort(police.begin(), police.end());
    police.erase(unique(police.begin(), police.end()), police.end());

    for (int x = 1; x <= n; ++x) {
        if (x != s && x != d && !binary_search(police.begin(), police.end(), x)) {
            candidates.push_back(x);
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int k = rnd.next(0, maxK);
    while ((int)police.size() > k) {
        police.erase(police.begin() + rnd.next((int)police.size()));
    }
    while ((int)police.size() < k && !candidates.empty()) {
        police.push_back(candidates.back());
        candidates.pop_back();
    }

    shuffle(police.begin(), police.end());
    return police;
}

static CaseData randomCase() {
    int n = rnd.next(2, 40);
    int s = rnd.next(1, n);
    int d = rnd.next(1, n - 1);
    if (d >= s) ++d;

    int f = rnd.next(0, min(100000, n + rnd.next(0, 8)));
    int b = rnd.next(0, min(100000, n + rnd.next(0, 8)));
    int maxK = min(n / 2, rnd.next(0, min(n / 2, 12)));

    return {n, s, d, f, b, choosePolice(n, s, d, maxK, {})};
}

static CaseData corridorCase(bool blockPath) {
    int n = rnd.next(8, 35);
    int step = rnd.next(1, 5);
    int f = step;
    int b = rnd.next(0, 3);
    int s = rnd.next(1, min(step, n - 1));

    vector<int> path;
    for (int x = s; x <= n; x += step) {
        path.push_back(x);
    }
    int d = path.back();
    if (d == s) {
        d = min(n, s + 1);
    }

    set<int> preferred;
    if (blockPath && path.size() >= 3) {
        preferred.insert(path[rnd.next(1, (int)path.size() - 2)]);
    }

    int maxK = min(n / 2, rnd.next(0, min(n / 2, 10)));
    return {n, s, d, f, b, choosePolice(n, s, d, maxK, preferred)};
}

static CaseData boundaryCase() {
    int n = rnd.next(2, 30);
    int s = rnd.next(1, n);
    int d = rnd.next(1, n - 1);
    if (d >= s) ++d;

    int f;
    int b;
    if (rnd.next(2) == 0) {
        f = 0;
        b = rnd.next(0, n + 5);
    } else {
        f = rnd.next(0, n + 5);
        b = 0;
    }

    int maxK = min(n / 2, rnd.next(0, min(n / 2, 8)));
    return {n, s, d, f, b, choosePolice(n, s, d, maxK, {})};
}

static CaseData densePoliceCase() {
    int n = rnd.next(10, 45);
    int s = rnd.next(1, n);
    int d = rnd.next(1, n - 1);
    if (d >= s) ++d;

    int f = rnd.next(1, min(12, n + 3));
    int b = rnd.next(1, min(12, n + 3));
    int maxK = n / 2;

    set<int> preferred;
    for (int delta = -2; delta <= 2; ++delta) {
        preferred.insert(s + delta);
        preferred.insert(d + delta);
        preferred.insert(s + f + delta);
        preferred.insert(s - b + delta);
    }

    return {n, s, d, f, b, choosePolice(n, s, d, maxK, preferred)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    CaseData tc;
    if (mode == 0) {
        tc = randomCase();
    } else if (mode == 1) {
        tc = corridorCase(false);
    } else if (mode == 2) {
        tc = corridorCase(true);
    } else {
        tc = rnd.next(2) == 0 ? boundaryCase() : densePoliceCase();
    }

    println(tc.n, tc.s, tc.d, tc.f, tc.b, (int)tc.police.size());
    if (!tc.police.empty()) {
        println(tc.police);
    }

    return 0;
}
