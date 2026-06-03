#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int q = rnd.next(1, 18);

    vector<int> a(n);
    vector<pair<int, int>> queries;

    if (mode == 0) {
        int hi = rnd.next(0, 12);
        for (int& v : a) v = rnd.next(0, hi);
        for (int i = 0; i < q; ++i) {
            int x = rnd.next(0, hi + 8);
            int y = rnd.any(vector<int>{0, 1, 2, 3, 5});
            queries.push_back({x, y});
        }
    } else if (mode == 1) {
        vector<int> pool = {0, 1, 2, 3, 4, 8, 16};
        for (int& v : a) v = rnd.any(pool);
        for (int i = 0; i < q; ++i) {
            int base = rnd.any(pool);
            int x = max(0, base + rnd.next(-1, 1));
            int y = rnd.next(0, 4);
            queries.push_back({x, y});
        }
    } else if (mode == 2) {
        for (int& v : a) v = rnd.next(0, 3) == 0 ? 0 : rnd.next(1, 25);
        for (int i = 0; i < q; ++i) {
            int x = rnd.next(0, 40);
            int y = (i % 3 == 0) ? 0 : rnd.next(1, 6);
            queries.push_back({x, y});
        }
    } else if (mode == 3) {
        int cur = rnd.next(1, 6);
        for (int& v : a) {
            cur += rnd.next(0, 4);
            v = cur;
        }
        shuffle(a.begin(), a.end());
        for (int i = 0; i < q; ++i) {
            int x = rnd.next(0, cur + 20);
            int y = rnd.next(1, 5);
            queries.push_back({x, y});
        }
    } else if (mode == 4) {
        vector<int> pool = {0, 1, 999999937, 1000000000};
        n = rnd.next(1, 6);
        q = rnd.next(1, 8);
        a.assign(n, 0);
        for (int& v : a) v = rnd.any(pool);
        for (int i = 0; i < q; ++i) {
            int x = rnd.any(pool);
            int y = rnd.any(vector<int>{0, 1, 2, 1000000000});
            queries.push_back({x, y});
        }
    } else {
        for (int& v : a) v = rnd.next(0, 30);
        sort(a.begin(), a.end());
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
        for (int i = 0; i < q; ++i) {
            int x = rnd.next(0, 60);
            int y = rnd.next(0, 3) == 0 ? 1 : rnd.next(0, 7);
            queries.push_back({x, y});
        }
    }

    println(n, q);
    println(a);
    for (auto [x, y] : queries) println(x, y);

    return 0;
}
