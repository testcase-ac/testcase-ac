#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, mode == 5 ? 40 : 16);

    vector<int> stones(n + 1);
    int valueMode = rnd.next(0, 4);
    for (int i = 1; i <= n; ++i) {
        if (valueMode == 0) {
            stones[i] = rnd.next(1, 12);
        } else if (valueMode == 1) {
            stones[i] = (i % 3 == 0 ? rnd.next(1, 4) : rnd.next(20, 80));
        } else if (valueMode == 2) {
            stones[i] = rnd.next(900000, 1000000);
        } else if (valueMode == 3) {
            stones[i] = i;
        } else {
            stones[i] = rnd.next(1, 1000000);
        }
    }

    vector<int> closed;
    if (mode == 0) {
        // Leave the whole circle connected.
    } else if (mode == 1) {
        closed.push_back(rnd.next(1, n));
    } else if (mode == 2) {
        int m = rnd.next(2, min(n, 5));
        vector<int> edges(n);
        iota(edges.begin(), edges.end(), 1);
        shuffle(edges.begin(), edges.end());
        closed.assign(edges.begin(), edges.begin() + m);
    } else if (mode == 3) {
        int step = rnd.next(2, 4);
        int start = rnd.next(1, step);
        for (int e = start; e <= n; e += step) closed.push_back(e);
    } else if (mode == 4) {
        int first = rnd.next(1, n);
        int len = rnd.next(1, min(n, 6));
        for (int t = 0; t < len; ++t) closed.push_back((first + t - 1) % n + 1);
    } else {
        for (int e = 1; e <= n; ++e) closed.push_back(e);
    }

    sort(closed.begin(), closed.end());
    closed.erase(unique(closed.begin(), closed.end()), closed.end());

    vector<char> isClosed(n + 1, false);
    for (int e : closed) isClosed[e] = true;

    vector<char> seen(n + 1, false);
    long long needed = 0;
    for (int start = 1; start <= n; ++start) {
        if (seen[start]) continue;
        int best = stones[start];
        int cur = start;
        while (!seen[cur]) {
            seen[cur] = true;
            best = min(best, stones[cur]);
            int edge = cur;
            int nxt = (cur == n ? 1 : cur + 1);
            if (isClosed[edge]) break;
            cur = nxt;
        }
        needed += best;
    }

    long long k;
    if (closed.empty()) {
        k = rnd.next(0LL, 5000000000LL);
    } else {
        int budgetMode = rnd.next(0, 3);
        if (budgetMode == 0) {
            k = max(0LL, needed - rnd.next(1LL, min(needed, 20LL)));
        } else if (budgetMode == 1) {
            k = needed;
        } else if (budgetMode == 2) {
            k = min(5000000000LL, needed + rnd.next(1LL, 50LL));
        } else {
            k = rnd.next(0LL, 5000000000LL);
        }
    }

    println(n, static_cast<int>(closed.size()), k);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << stones[i];
    }
    cout << '\n';

    shuffle(closed.begin(), closed.end());
    for (int e : closed) {
        if (e == n) {
            if (rnd.next(0, 1) == 0) println(n, 1);
            else println(1, n);
        } else {
            if (rnd.next(0, 1) == 0) println(e, e + 1);
            else println(e + 1, e);
        }
    }

    return 0;
}
