#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int c;
    vector<tuple<int, int, int>> groups;

    auto addGroup = [&](int s, int e, int m) {
        groups.emplace_back(s, e, m);
    };

    if (mode == 0) {
        n = 2;
        c = rnd.next(1, 3);
        addGroup(1, 2, rnd.next(1, n));
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        c = rnd.next(1, 8);
        for (int s = 1; s < n; ++s) {
            int e = rnd.next(s + 1, n);
            addGroup(s, e, rnd.next(1, n));
        }
    } else if (mode == 2) {
        n = rnd.next(5, 18);
        c = rnd.next(1, 10);
        int k = rnd.next(n, min(3 * n, 45));
        for (int i = 0; i < k; ++i) {
            int s = rnd.next(1, max(1, n / 2));
            int e = rnd.next(max(s + 1, n / 2 + 1), n);
            addGroup(s, e, rnd.next(1, n));
        }
    } else if (mode == 3) {
        n = rnd.next(6, 20);
        c = rnd.next(1, 12);
        int hubs = rnd.next(2, min(5, n - 1));
        for (int i = 0; i < hubs; ++i) {
            int s = rnd.next(1, n - 1);
            int e = rnd.next(s + 1, n);
            int copies = rnd.next(2, 6);
            for (int j = 0; j < copies; ++j) {
                addGroup(s, e, rnd.next(1, n));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(8, 30);
        c = rnd.next(1, 100);
        int k = rnd.next(20, 80);
        for (int i = 0; i < k; ++i) {
            int s = rnd.next(1, n - 1);
            int maxLen = min(n - s, rnd.next(1, 8));
            int e = s + rnd.next(1, maxLen);
            addGroup(s, e, rnd.next(1, n));
        }
    } else {
        n = rnd.next(2, 25);
        c = rnd.next(1, 100);
        int k = rnd.next(1, 60);
        for (int i = 0; i < k; ++i) {
            int s = rnd.next(1, n - 1);
            int e = rnd.next(s + 1, n);
            addGroup(s, e, rnd.next(1, n));
        }
    }

    shuffle(groups.begin(), groups.end());

    println(static_cast<int>(groups.size()), n, c);
    for (auto [s, e, m] : groups) {
        println(s, e, m);
    }

    return 0;
}
