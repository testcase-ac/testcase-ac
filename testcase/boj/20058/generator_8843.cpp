#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, Q;
    int S;
    vector<vector<int>> A;

    int scenario = rnd.next(0, 5); // 0..5

    if (scenario == 0) {
        // General random small/medium case
        N = rnd.next(2, 3);
        S = 1 << N;
        A.assign(S, vector<int>(S));
        for (int i = 0; i < S; ++i)
            for (int j = 0; j < S; ++j)
                A[i][j] = rnd.next(0, 7); // small values, many zeros

        Q = rnd.next(1, 10);
    } else if (scenario == 1) {
        // All zero grid
        N = rnd.next(2, 3);
        S = 1 << N;
        A.assign(S, vector<int>(S, 0));
        Q = rnd.next(1, 10);
    } else if (scenario == 2) {
        // All equal non-zero values
        N = rnd.next(2, 3);
        S = 1 << N;
        int val;
        if (rnd.next(0, 4) == 0) val = 100; // sometimes max value
        else val = rnd.next(1, 7);
        A.assign(S, vector<int>(S, val));
        Q = rnd.next(3, 15); // a bit longer sequence
    } else if (scenario == 3) {
        // Checkerboard pattern
        N = 3; // fixed to get an 8x8 checkerboard
        S = 1 << N;
        A.assign(S, vector<int>(S, 0));
        int v1 = rnd.next(1, 5);
        int v2 = (rnd.next(0, 1) ? 0 : rnd.next(1, 5));
        for (int i = 0; i < S; ++i) {
            for (int j = 0; j < S; ++j) {
                if ((i + j) % 2 == 0) A[i][j] = v1;
                else A[i][j] = v2;
            }
        }
        Q = rnd.next(2, 10);
    } else if (scenario == 4) {
        // One large connected blob plus some isolated cells
        N = rnd.next(2, 3);
        S = 1 << N;
        A.assign(S, vector<int>(S, 0));

        // Visited array
        vector<vector<bool>> vis(S, vector<bool>(S, false));

        int sr = rnd.next(0, S - 1);
        int sc = rnd.next(0, S - 1);

        int totalCells = S * S;
        int target = rnd.next(S / 2, min(totalCells, S + totalCells / 3)); // medium-sized blob

        vector<pair<int,int>> q;
        q.push_back(make_pair(sr, sc));
        vis[sr][sc] = true;
        int count = 1;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        for (int qi = 0; qi < (int)q.size() && count < target; ++qi) {
            int r = q[qi].first;
            int c = q[qi].second;
            // randomize neighbor order
            vector<int> dirs = {0, 1, 2, 3};
            shuffle(dirs.begin(), dirs.end());
            for (int k = 0; k < 4 && count < target; ++k) {
                int d = dirs[k];
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < 0 || nr >= S || nc < 0 || nc >= S) continue;
                if (vis[nr][nc]) continue;
                vis[nr][nc] = true;
                q.push_back(make_pair(nr, nc));
                ++count;
            }
        }

        // Assign random small values to blob cells
        for (auto &p : q) {
            int r = p.first;
            int c = p.second;
            A[r][c] = rnd.next(1, 7);
        }

        // Add a few isolated single cells with small value
        int extraSingles = rnd.next(1, max(1, S / 2));
        while (extraSingles--) {
            int r = rnd.next(0, S - 1);
            int c = rnd.next(0, S - 1);
            if (A[r][c] == 0) {
                A[r][c] = rnd.next(1, 3);
            }
        }

        Q = rnd.next(2, 12);
    } else if (scenario == 5) {
        // Border-heavy: edges high, center low/zero
        N = rnd.next(2, 3);
        S = 1 << N;
        A.assign(S, vector<int>(S, 0));
        int edgeHigh = rnd.next(4, 9);
        int innerLow = rnd.next(0, 3);

        for (int i = 0; i < S; ++i) {
            for (int j = 0; j < S; ++j) {
                bool isEdge = (i == 0 || i == S - 1 || j == 0 || j == S - 1);
                if (isEdge) A[i][j] = edgeHigh;
                else A[i][j] = innerLow;
            }
        }

        Q = rnd.next(3, 10);
    }

    // Generate L sequence with some structure
    vector<int> L(Q);
    if (Q == 1) {
        // Ensure single-step includes interesting levels
        int choice = rnd.next(0, 2);
        if (choice == 0) L[0] = 0;
        else if (choice == 1) L[0] = N;
        else L[0] = rnd.next(0, N);
    } else {
        for (int i = 0; i < Q; ++i) {
            int mode = rnd.next(0, 3);
            if (mode == 0) {
                L[i] = 0; // many L=0 to test no-rotation cases
            } else if (mode == 1) {
                L[i] = N; // full-size rotation
            } else if (mode == 2 && N > 1) {
                L[i] = rnd.next(1, N - 1); // proper subgrid rotation
            } else {
                L[i] = rnd.next(0, N);
            }
        }

        // With some probability, make a patterned sequence (e.g., 0,1,2,...)
        if (rnd.next(0, 4) == 0) {
            for (int i = 0; i < Q; ++i) {
                L[i] = i % (N + 1);
            }
        }
    }

    // Output
    println(N, Q);
    for (int i = 0; i < (1 << N); ++i)
        println(A[i]);
    println(L);

    return 0;
}
