#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int otherPlayer(int winner, int n) {
    int loser = rnd.next(1, n - 1);
    if (loser >= winner) ++loser;
    return loser;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    vector<pair<int, int>> duels;

    if (mode == 0) {
        // Sparse case, including possible zero-match inputs.
        int m = rnd.next(0, min(12, 2 * n));
        for (int i = 0; i < m; ++i) {
            int a = rnd.next(1, n);
            duels.emplace_back(a, otherPlayer(a, n));
        }
    } else if (mode == 1) {
        // Many equal scores, useful for ranking tie handling.
        int groupScore = rnd.next(0, 4);
        for (int a = 1; a <= n; ++a) {
            for (int k = 0; k < groupScore; ++k) {
                duels.emplace_back(a, otherPlayer(a, n));
            }
        }
    } else if (mode == 2) {
        // Already separated or nearly separated score ladder.
        for (int a = 1; a <= n; ++a) {
            int wins = a - 1;
            if (rnd.next(0, 4) == 0 && wins > 0) --wins;
            for (int k = 0; k < wins; ++k) {
                duels.emplace_back(a, otherPlayer(a, n));
            }
        }
    } else if (mode == 3) {
        // One or two dominant players mixed with low scores.
        int stars = rnd.next(1, min(2, n));
        for (int a = 1; a <= n; ++a) {
            int wins = (a <= stars) ? rnd.next(n / 2, n + 6) : rnd.next(0, 2);
            for (int k = 0; k < wins; ++k) {
                duels.emplace_back(a, otherPlayer(a, n));
            }
        }
    } else if (mode == 4) {
        // Cyclic-looking results where labels and scores are not aligned.
        int rounds = rnd.next(1, 5);
        for (int r = 0; r < rounds; ++r) {
            for (int a = 1; a <= n; ++a) {
                int b = (a == n) ? 1 : a + 1;
                if (rnd.next(0, 1)) duels.emplace_back(a, b);
                else duels.emplace_back(b, a);
            }
        }
    } else {
        // Medium random case with repeated pair results allowed.
        int m = rnd.next(n, min(80, 6 * n));
        for (int i = 0; i < m; ++i) {
            int a = rnd.next(1, n);
            duels.emplace_back(a, otherPlayer(a, n));
        }
    }

    if ((int)duels.size() > 200000) duels.resize(200000);
    shuffle(duels.begin(), duels.end());

    println(n, (int)duels.size());
    for (auto [a, b] : duels) {
        println(a, b);
    }

    return 0;
}
