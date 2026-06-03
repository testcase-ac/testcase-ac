#include "testlib.h"

#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int k;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 4);
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        m = rnd.next(1, 5);
        k = rnd.next(1, n);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
        m = rnd.next(2, 8);
        k = rnd.next(max(1, n - 3), n);
    } else {
        n = rnd.next(3, 10);
        m = rnd.next(3, 10);
        k = rnd.next(1, n);
    }

    println(n, m, k);

    vector<int> best(n + 1, 0);
    for (int student = 1; student <= n; ++student) {
        best[student] = rnd.next(0, 100);
    }

    for (int genre = 0; genre < m; ++genre) {
        vector<pair<int, int>> scores;
        scores.reserve(n);

        int favorite = rnd.next(1, n);
        int bandLo = rnd.next(0, 7) * 10;
        int bandHi = rnd.next(bandLo, 100);

        for (int student = 1; student <= n; ++student) {
            int score;
            if (mode == 0) {
                score = rnd.next(0, 100);
            } else if (mode == 1) {
                score = rnd.next(0, 20) * 5;
            } else if (mode == 2) {
                score = max(0, best[student] - rnd.next(0, 25));
            } else if (mode == 3) {
                score = (student == favorite) ? rnd.next(80, 100) : rnd.next(0, 75);
            } else if (mode == 4) {
                score = rnd.next(bandLo, bandHi);
            } else {
                score = rnd.next(0, 10) * 10;
            }
            scores.emplace_back(score, student);
        }

        shuffle(scores.begin(), scores.end());
        sort(scores.begin(), scores.end(), [](const pair<int, int>& left,
                                               const pair<int, int>& right) {
            return left.first > right.first;
        });

        for (int pos = 0; pos < n; ++pos) {
            if (pos) {
                putchar(' ');
            }
            printf("%d %.1f", scores[pos].second, scores[pos].first / 10.0);
        }
        putchar('\n');
    }

    return 0;
}
