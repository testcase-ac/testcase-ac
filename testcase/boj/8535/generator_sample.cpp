#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

using Query = tuple<long long, long long, int>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(0, 24);
    vector<Query> queries;
    queries.reserve(n);

    int mode = rnd.next(0, 4);
    long long maxCoord = rnd.next(1, 60);
    if (rnd.next(0, 5) == 0) maxCoord = 1000000000LL;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            long long b = rnd.next(1LL, maxCoord);
            long long e = rnd.next(b, min(maxCoord, b + rnd.next(0LL, 12LL)));
            queries.emplace_back(b, e, rnd.next(0, 1));
        }
    } else {
        int points = max(1, min(16, n + 2));
        vector<long long> bit(points + 1);
        for (int i = 0; i <= points; ++i) bit[i] = rnd.next(0, 1);

        for (int i = 0; i < n; ++i) {
            int left = rnd.next(1, points);
            int right = rnd.next(left, points);
            long long b = left;
            long long e = right;

            if (mode == 2 && rnd.next(0, 3) == 0) {
                b = rnd.next(1LL, maxCoord);
                e = rnd.next(b, min(maxCoord, b + rnd.next(0LL, 20LL)));
            }

            int s = static_cast<int>(bit[right] ^ bit[left - 1]);
            queries.emplace_back(b, e, s);
        }

        if (!queries.empty() && (mode == 3 || mode == 4)) {
            int pos = mode == 3 ? static_cast<int>(queries.size()) - 1 : rnd.next(0, static_cast<int>(queries.size()) - 1);
            auto [b, e, s] = queries[pos];
            queries[pos] = Query(b, e, 1 - s);
        }

        if (mode == 4) {
            shuffle(queries.begin(), queries.end());
        }
    }

    println(static_cast<int>(queries.size()));
    for (const auto& [b, e, s] : queries) {
        println(b, e, s);
    }

    return 0;
}
