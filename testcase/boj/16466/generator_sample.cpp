#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxTicket = 2147483647;
    int mode = rnd.next(0, 6);
    vector<int> tickets;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        for (int i = 1; i <= n; ++i) {
            tickets.push_back(i);
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 16);
        int missing = rnd.next(1, n + 1);
        for (int x = 1; (int)tickets.size() < n; ++x) {
            if (x != missing) {
                tickets.push_back(x);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(1, 18);
        int lo = rnd.next(2, 30);
        int hi = rnd.next(lo, lo + 40);
        for (int i = 0; i < n; ++i) {
            tickets.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 25);
        int poolSize = rnd.next(1, min(6, n));
        vector<int> pool;
        for (int i = 0; i < poolSize; ++i) {
            pool.push_back(rnd.next(1, 12));
        }
        for (int i = 0; i < n; ++i) {
            tickets.push_back(rnd.any(pool));
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 15);
        for (int i = 0; i < n; ++i) {
            tickets.push_back(maxTicket - rnd.next(0, 200));
        }
        if (rnd.next(0, 1)) {
            tickets[rnd.next(0, n - 1)] = rnd.next(1, 5);
        }
    } else if (mode == 5) {
        int n = rnd.next(30, 80);
        int limit = rnd.next(n, n * 3);
        for (int i = 0; i < n; ++i) {
            tickets.push_back(rnd.next(1, limit));
        }
    } else {
        int n = rnd.next(80, 180);
        int prefix = rnd.next(1, min(n, 120));
        for (int i = 1; i <= prefix; ++i) {
            tickets.push_back(i);
        }
        while ((int)tickets.size() < n) {
            tickets.push_back(rnd.next(1, maxTicket));
        }
    }

    int order = rnd.next(0, 2);
    if (order == 0) {
        sort(tickets.begin(), tickets.end());
    } else if (order == 1) {
        sort(tickets.rbegin(), tickets.rend());
    } else {
        shuffle(tickets.begin(), tickets.end());
    }

    println(static_cast<int>(tickets.size()));
    println(tickets);

    return 0;
}
