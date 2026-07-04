#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    vector<vector<long long>> allA;
    vector<vector<long long>> allB;
    allA.reserve(t);
    allB.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0 && rnd.next(4) == 0) {
            n = 1;
        } else {
            n = rnd.next(2, 12);
        }

        vector<long long> wins(n, 0), draws(n, 0);
        if (n > 1) {
            int winStyle = rnd.next(4);
            for (int i = 0; i < n; ++i) {
                if (winStyle == 0) {
                    wins[i] = rnd.next(0, 3);
                } else if (winStyle == 1) {
                    wins[i] = (i == 0 ? rnd.next(0, 8) : rnd.next(0, 2));
                } else if (winStyle == 2) {
                    wins[i] = rnd.next(0, i + 2);
                } else {
                    wins[i] = rnd.wnext(12, -2);
                }
            }

            vector<pair<int, int>> pairs;
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    pairs.emplace_back(i, j);
                }
            }
            shuffle(pairs.begin(), pairs.end());

            int drawGames = rnd.next(0, min(18, n * (n - 1)));
            for (int k = 0; k < drawGames; ++k) {
                auto [u, v] = pairs[rnd.next((int)pairs.size())];
                ++draws[u];
                ++draws[v];
            }
        }

        vector<long long> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            a[i] = 2 * wins[i] + draws[i];
            b[i] = 3 * wins[i] + draws[i];
        }

        allA.push_back(a);
        allB.push_back(b);
    }

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        println((int)allA[tc].size());
        println(allA[tc]);
        println(allB[tc]);
    }

    return 0;
}
