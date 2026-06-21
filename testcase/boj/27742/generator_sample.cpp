#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long pickScore(long long k, int mode) {
    if (mode == 0) {
        return rnd.next(0, 6);
    }
    if (mode == 1) {
        return rnd.next(0, 1);
    }
    if (mode == 2) {
        return rnd.next(0, 20);
    }
    if (mode == 3) {
        vector<long long> candidates = {0, 1, 2, 3, k};
        if (k > 1000) {
            candidates.push_back(1000);
            candidates.push_back(k - 1);
            candidates.push_back(k / 2);
        }
        return rnd.any(candidates);
    }
    return rnd.next(0LL, min(k, 1000000LL));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 4);
    long long k = rnd.next(0, 4) == 0 ? 1000000000000LL : rnd.next(1000LL, 1000000LL);
    int missingOpponent = rnd.next(1, 3);
    if (missingOpponent >= t) {
        ++missingOpponent;
    }

    int mode = rnd.next(0, 4);
    long long score[4][4] = {};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == j) {
                score[i][j] = 0;
            } else {
                score[i][j] = pickScore(k, mode);
            }
        }
    }

    if (mode == 1) {
        long long base = rnd.next(0, 3);
        for (int i = 0; i < 4; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                score[i][j] = base;
                score[j][i] = base;
            }
        }
    } else if (mode == 2) {
        for (int j = 0; j < 4; ++j) {
            if (j != t - 1) {
                score[t - 1][j] = rnd.next(0, 4);
                score[j][t - 1] = rnd.next(3, 9);
            }
        }
    } else if (mode == 3) {
        for (int j = 0; j < 4; ++j) {
            if (j != t - 1) {
                score[t - 1][j] = rnd.any(vector<long long>{0, 1, k});
            }
        }
    }

    score[t - 1][missingOpponent - 1] = -1;

    println(t, k);
    for (int i = 0; i < 4; ++i) {
        println(score[i][0], score[i][1], score[i][2], score[i][3]);
    }

    return 0;
}
