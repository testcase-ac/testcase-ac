#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int boundedScore(int value) {
    return max(1, min(200000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int k = rnd.next(2, 10);

    if (mode == 0) {
        n = 1;
        k = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        k = 1;
    } else if (mode == 5) {
        n = rnd.next(20, 40);
        k = rnd.next(12, 25);
    }

    vector<vector<int>> score(n, vector<int>(k));
    int base = rnd.next(1, 199950);

    if (mode == 0) {
        for (int j = 0; j < k; ++j) {
            score[0][j] = rnd.next(1, 200000);
        }
    } else if (mode == 1) {
        int high = rnd.next(100000, 200000);
        int winner = rnd.next(0, n - 1);
        bool tieHigh = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            score[i][0] = rnd.next(1, high);
        }
        score[winner][0] = high;
        if (tieHigh && n > 1) {
            int other = rnd.next(0, n - 2);
            if (other >= winner) ++other;
            score[other][0] = high;
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                score[i][j] = boundedScore(base + rnd.next(0, 20));
            }
        }
        vector<int> people(n);
        for (int i = 0; i < n; ++i) people[i] = i;
        shuffle(people.begin(), people.end());
        for (int j = 0; j < k; ++j) {
            int owner = people[j % n];
            score[owner][j] = 200000 - j;
        }
    } else if (mode == 3) {
        int value = rnd.next(50000, 150000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                score[i][j] = boundedScore(value + rnd.next(-2, 2));
            }
        }
        for (int j = 0; j < k; ++j) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            score[a][j] = value + 3;
            score[b][j] = value + 3;
        }
    } else if (mode == 4) {
        int step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                int trend = (i + 1) * step + (k - j) * rnd.next(0, 3);
                score[i][j] = boundedScore(base + trend);
            }
        }
        if (rnd.next(0, 1)) {
            reverse(score.begin(), score.end());
        }
    } else {
        int lo = rnd.next(1, 190000);
        int hi = rnd.next(lo, min(200000, lo + rnd.next(5, 10000)));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                score[i][j] = rnd.next(lo, hi);
            }
        }
    }

    println(n, k);
    for (const auto& row : score) {
        println(row);
    }

    return 0;
}
