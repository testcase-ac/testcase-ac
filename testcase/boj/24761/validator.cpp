#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1;
    const int N_MAX = 1000;
    const int R_MIN = 0;
    const int R_MAX = 10000;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int R = inf.readInt(R_MIN, R_MAX, "R");
    inf.readEoln();

    // current teams string: length N, chars A/B
    string cur = inf.readToken("[AB]{1,1000}", "current_teams");
    inf.readEoln();
    ensuref((int)cur.size() == N,
            "current_teams length must be exactly N (%d), got %d",
            N, (int)cur.size());

    // requested teams string: length N, chars A/B/?
    string req = inf.readToken("[AB\\?]{1,1000}", "requested_teams");
    inf.readEoln();
    ensuref((int)req.size() == N,
            "requested_teams length must be exactly N (%d), got %d",
            N, (int)req.size());

    // Read rivalries, ensure constraints: 1 <= i,j <= N, i != j, no duplicates.
    set<pair<int,int>> edges;
    for (int k = 0; k < R; ++k) {
        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int j = inf.readInt(1, N, "j");
        inf.readEoln();

        ensuref(i != j, "Rivalry %d is a loop: (%d, %d)", k + 1, i, j);
        ensuref(cur[i - 1] != cur[j - 1],
                "Rivalry %d has students on the same current team: (%d, %d)",
                k + 1, i, j);

        int a = i, b = j;
        if (a > b) swap(a, b);
        pair<int,int> e = {a, b};
        ensuref(!edges.count(e),
                "Duplicate rivalry at index %d: (%d, %d)", k + 1, i, j);
        edges.insert(e);
    }

    inf.readEof();
}
