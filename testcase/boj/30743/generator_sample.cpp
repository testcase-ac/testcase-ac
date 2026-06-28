#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000000000000LL;
    int mode = rnd.next(0, 5);
    long long n;

    if (mode == 0) {
        n = rnd.next(1LL, 12LL);
    } else if (mode == 1) {
        int k = rnd.next(1, 20);
        long long base = 1LL << k;
        n = max(1LL, base + rnd.next(-2LL, 2LL));
    } else if (mode == 2) {
        long long base = 1LL << rnd.next(20, 50);
        n = min(LIMIT, max(1LL, base + rnd.next(-1000LL, 1000LL)));
    } else if (mode == 3) {
        n = LIMIT - rnd.next(0LL, 1000LL);
    } else if (mode == 4) {
        n = rnd.next(1LL, 1000000LL);
    } else {
        n = rnd.next(1LL, LIMIT);
    }

    int q = rnd.next(1, 20);
    vector<long long> queries;
    queries.reserve(q);

    vector<long long> anchors = {1, n};
    for (long long x : {2LL, 3LL, 4LL, 5LL, n / 2, (n + 1) / 2, n - 1, n - 2, n - 3}) {
        if (1 <= x && x <= n) {
            anchors.push_back(x);
        }
    }

    while ((int)queries.size() < q) {
        int pick = rnd.next(0, 3);
        if (pick == 0 && !anchors.empty()) {
            queries.push_back(rnd.any(anchors));
        } else if (pick == 1) {
            long long width = min(n, 1000LL);
            queries.push_back(rnd.next(1LL, width));
        } else if (pick == 2) {
            long long width = min(n, 1000LL);
            queries.push_back(n - rnd.next(0LL, width - 1));
        } else {
            queries.push_back(rnd.next(1LL, n));
        }
    }

    shuffle(queries.begin(), queries.end());

    println(n, q);
    for (long long x : queries) {
        println(x);
    }

    return 0;
}
