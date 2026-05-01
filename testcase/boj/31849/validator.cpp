#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 2, N_MAX = 1000;
    const int M_MIN = 2, M_MAX = 1000;
    const int P_MIN = 1, P_MAX = 100;
    const long long RC_MAX = 500000LL;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int M = inf.readInt(M_MIN, M_MAX, "M");
    inf.readSpace();
    int R = inf.readInt(1, N * M, "R"); // at least 1 room (given)
    inf.readSpace();
    int C = inf.readInt(1, N * M, "C"); // at least 1 convenience store (given)
    inf.readEoln();

    long long RCsum = 1LL * R + 1LL * C;
    ensuref(RCsum >= 2, "Constraint violated: R + C must be at least 2, got %lld", RCsum);
    long long cells = 1LL * N * M;
    ensuref(RCsum <= cells,
            "Constraint violated: R + C = %lld exceeds N*M = %lld", RCsum, cells);
    ensuref(RCsum <= RC_MAX,
            "Constraint violated: R + C = %lld exceeds 5*10^5", RCsum);

    // Track occupied cells: 0 = empty, 1 = room, 2 = convenience store
    vector<char> used(N * M, 0);

    auto idx = [&](int x, int y) -> int {
        // x in [1,N], y in [1,M]
        return (x - 1) * M + (y - 1);
    };

    vector<int> room_x(R), room_y(R);
    vector<int> rent(R);

    for (int i = 0; i < R; ++i) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, M, "b_i");
        inf.readSpace();
        int p = inf.readInt(P_MIN, P_MAX, "p_i");
        inf.readEoln();

        int id = idx(a, b);
        ensuref(used[id] == 0,
                "Duplicate or conflicting position for room at index %d: (%d,%d)", i + 1, a, b);
        used[id] = 1;

        room_x[i] = a;
        room_y[i] = b;
        rent[i]   = p;
    }

    vector<int> conv_x(C), conv_y(C);
    for (int j = 0; j < C; ++j) {
        int c = inf.readInt(1, N, "c_j");
        inf.readSpace();
        int d = inf.readInt(1, M, "d_j");
        inf.readEoln();

        int id = idx(c, d);
        ensuref(used[id] == 0,
                "Duplicate or conflicting position for convenience store at index %d: (%d,%d)",
                j + 1, c, d);
        used[id] = 2;

        conv_x[j] = c;
        conv_y[j] = d;
    }

    // Global property: For all rooms, the "nearest convenience store" must exist,
    // and the answer (minimum score) must fit into 64-bit signed integer.
    // We enforce that by explicitly computing it (potentially O(R*C), acceptable for validation).
    const long long INF = (1LL << 62);
    long long bestScore = INF;

    for (int i = 0; i < R; ++i) {
        long long bestDist = INF;
        for (int j = 0; j < C; ++j) {
            long long dx = llabs((long long)room_x[i] - (long long)conv_x[j]);
            long long dy = llabs((long long)room_y[i] - (long long)conv_y[j]);
            long long dist = dx + dy;
            if (dist < bestDist) bestDist = dist;
        }
        // There is at least one convenience store, so bestDist < INF
        ensuref(bestDist < INF,
                "No convenience store found for room index %d at (%d,%d)",
                i + 1, room_x[i], room_y[i]);

        long long score = bestDist * (long long)rent[i];
        ensuref(score >= 0 && score <= (long long)4e8 * P_MAX,
                "Score overflow or unreasonable score for room index %d: %lld",
                i + 1, score);
        if (score < bestScore) bestScore = score;
    }

    ensuref(bestScore < INF, "No valid room score computed (internal error)");

    inf.readEof();
}
