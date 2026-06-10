#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    if (mode == 5) {
        n = rnd.next(20, 45);
    }
    int k = rnd.next(1, n);

    vector<pair<int, int>> games;
    games.reserve(n);

    if (mode == 0) {
        int c = rnd.next(1, 30);
        int h = rnd.next(1, 30);
        for (int i = 1; i <= n; ++i) {
            games.push_back({c, h});
        }
    } else if (mode == 1) {
        int ratio = rnd.next(1, 12);
        for (int i = 1; i <= n; ++i) {
            int c = rnd.next(1, 50);
            games.push_back({c, c * ratio});
        }
    } else if (mode == 2) {
        int c = rnd.next(1, 100);
        for (int i = 1; i <= n; ++i) {
            games.push_back({c, rnd.next(1, 1000)});
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            int c = rnd.any(vector<int>{1, 2, 3, 5, 10, 100000000});
            int h = rnd.any(vector<int>{1, 2, 3, 5, 10, 100000000});
            games.push_back({c, h});
        }
    } else {
        int maxValue = (mode == 5 ? 100000000 : rnd.next(20, 500));
        for (int i = 1; i <= n; ++i) {
            int c = rnd.next(1, maxValue);
            int h = rnd.next(1, maxValue);
            games.push_back({c, h});
        }
    }

    vector<int> ids(n);
    for (int i = 0; i < n; ++i) {
        ids[i] = i + 1;
    }
    shuffle(ids.begin(), ids.end());

    println(n, k);
    for (int row = 0; row < n; ++row) {
        println(ids[row], games[row].first, games[row].second);
    }

    return 0;
}
