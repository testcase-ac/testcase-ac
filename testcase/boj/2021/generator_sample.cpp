#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    int l = rnd.next(1, 10);
    vector<vector<int>> lines(l);

    auto randomStation = [&]() {
        return rnd.next(1, n);
    };

    if (mode == 0) {
        int hub = randomStation();
        for (int i = 0; i < l; ++i) {
            int len = rnd.next(1, min(n + 2, 8));
            lines[i].push_back(hub);
            for (int j = 1; j < len; ++j) lines[i].push_back(randomStation());
            shuffle(lines[i].begin(), lines[i].end());
        }
    } else if (mode == 1) {
        int cur = randomStation();
        for (int i = 0; i < l; ++i) {
            int next = randomStation();
            lines[i].push_back(cur);
            lines[i].push_back(next);
            int extras = rnd.next(0, 3);
            for (int j = 0; j < extras; ++j) lines[i].push_back(randomStation());
            cur = next;
        }
    } else if (mode == 2) {
        for (int i = 0; i < l; ++i) {
            int len = rnd.next(1, 7);
            int base = randomStation();
            for (int j = 0; j < len; ++j) {
                lines[i].push_back(rnd.next(0, 3) == 0 ? base : randomStation());
            }
        }
    } else if (mode == 3) {
        int split = max(1, n / 2);
        for (int i = 0; i < l; ++i) {
            bool upper = rnd.next(0, 1);
            int lo = upper ? split + 1 : 1;
            int hi = upper ? n : split;
            if (lo > hi) lo = hi = 1;
            int len = rnd.next(1, min(hi - lo + 3, 7));
            for (int j = 0; j < len; ++j) lines[i].push_back(rnd.next(lo, hi));
        }
    } else if (mode == 4) {
        int len = min(n, rnd.next(1, 12));
        for (int i = 0; i < l; ++i) {
            int start = rnd.next(1, max(1, n - len + 1));
            int take = rnd.next(1, len);
            for (int j = 0; j < take; ++j) lines[i].push_back(start + j);
        }
    } else {
        n = rnd.next(1, 6);
        l = rnd.next(1, 5);
        lines.assign(l, {});
        for (int i = 0; i < l; ++i) lines[i].push_back(randomStation());
    }

    int source;
    int destination;
    if (rnd.next(0, 5) == 0) {
        source = destination = randomStation();
    } else if (mode == 3 && n >= 2 && rnd.next(0, 1)) {
        int split = max(1, n / 2);
        source = rnd.next(1, split);
        destination = rnd.next(split + 1, n);
    } else {
        vector<int> seen;
        set<int> used;
        for (const auto& line : lines) {
            for (int station : line) {
                if (used.insert(station).second) seen.push_back(station);
            }
        }
        source = rnd.any(seen);
        destination = rnd.next(0, 2) == 0 ? rnd.any(seen) : randomStation();
    }

    println(n, l);
    for (const auto& line : lines) {
        for (int station : line) printf("%d ", station);
        println(-1);
    }
    println(source, destination);

    return 0;
}
