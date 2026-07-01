#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makeVisits(int n, int m, int mode) {
    vector<pair<int, int>> visits;
    visits.reserve(m);

    if (mode == 0) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        for (int i = 0; i < m; ++i) {
            visits.push_back(i % 2 == 0 ? make_pair(a, b) : make_pair(b, a));
        }
    } else if (mode == 1) {
        for (int i = 0; i < m; ++i) {
            int a = i % n + 1;
            int b = (i + 1) % n + 1;
            visits.emplace_back(a, b);
        }
    } else if (mode == 2) {
        int hub = rnd.next(1, n);
        for (int i = 0; i < m; ++i) {
            int other = rnd.next(1, n - 1);
            if (other >= hub) ++other;
            if (rnd.next(0, 1)) {
                visits.emplace_back(other, hub);
            } else {
                visits.emplace_back(hub, other);
            }
        }
    } else {
        for (int i = 0; i < m; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) ++b;
            visits.emplace_back(a, b);
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(visits.begin(), visits.end());
    }
    return visits;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 6);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 3);
        int n = mode == 0 ? rnd.next(2, 4) : rnd.next(2, 9);
        int m = rnd.next(1, 18);

        println(n, m);
        vector<pair<int, int>> visits = makeVisits(n, m, mode);
        for (const auto& visit : visits) {
            println(visit.first, visit.second);
        }
    }

    return 0;
}
