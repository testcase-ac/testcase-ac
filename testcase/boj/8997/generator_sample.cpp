#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    vector<int> wins;
    vector<int> defeats;
    vector<vector<int>> remaining;
};

CaseData makeCase(int mode) {
    CaseData tc;
    if (mode == 0) {
        tc.n = 1;
    } else if (mode == 1) {
        tc.n = rnd.next(2, 4);
    } else if (mode == 2) {
        tc.n = rnd.next(5, 9);
    } else {
        tc.n = rnd.next(10, 25);
    }

    tc.remaining.assign(tc.n, vector<int>(tc.n, 0));
    int maxRowSum = 0;
    for (int i = 0; i < tc.n; ++i) {
        for (int j = i + 1; j < tc.n; ++j) {
            int games = 0;
            if (mode == 1) {
                games = rnd.next(0, 3);
            } else if (mode == 2) {
                games = rnd.next(0, 6);
            } else if (mode == 3) {
                games = rnd.wnext(11, 2);
            }
            tc.remaining[i][j] = tc.remaining[j][i] = games;
        }
    }

    vector<int> rowSums(tc.n, 0);
    for (int i = 0; i < tc.n; ++i) {
        rowSums[i] = accumulate(tc.remaining[i].begin(), tc.remaining[i].end(), 0);
        maxRowSum = max(maxRowSum, rowSums[i]);
    }

    int seasonTotal = maxRowSum + rnd.next(0, 20);
    tc.wins.resize(tc.n);
    tc.defeats.resize(tc.n);
    for (int i = 0; i < tc.n; ++i) {
        int played = seasonTotal - rowSums[i];
        if (mode == 0) {
            tc.wins[i] = rnd.next(0, played);
        } else if (mode == 1) {
            tc.wins[i] = rnd.next(0, played);
        } else if (mode == 2) {
            tc.wins[i] = rnd.next(max(0, played / 2 - 3), min(played, played / 2 + 3));
        } else {
            tc.wins[i] = rnd.any(vector<int>{0, played, rnd.next(0, played)});
        }
        tc.defeats[i] = played - tc.wins[i];
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 8);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        CaseData data = makeCase(tc % 4);
        if (rnd.next(2) == 1) {
            vector<int> order(data.n);
            iota(order.begin(), order.end(), 0);
            shuffle(order.begin(), order.end());

            CaseData shuffled;
            shuffled.n = data.n;
            shuffled.wins.resize(data.n);
            shuffled.defeats.resize(data.n);
            shuffled.remaining.assign(data.n, vector<int>(data.n, 0));
            for (int i = 0; i < data.n; ++i) {
                shuffled.wins[i] = data.wins[order[i]];
                shuffled.defeats[i] = data.defeats[order[i]];
                for (int j = 0; j < data.n; ++j) {
                    shuffled.remaining[i][j] = data.remaining[order[i]][order[j]];
                }
            }
            data = shuffled;
        }

        println(data.n);
        for (int i = 0; i < data.n; ++i) {
            if (i > 0) {
                cout << ' ';
            }
            cout << data.wins[i] << ' ' << data.defeats[i];
        }
        cout << '\n';

        for (int i = 0; i < data.n; ++i) {
            for (int j = 0; j < data.n; ++j) {
                if (i > 0 || j > 0) {
                    cout << ' ';
                }
                cout << data.remaining[i][j];
            }
        }
        cout << '\n';
    }

    return 0;
}
