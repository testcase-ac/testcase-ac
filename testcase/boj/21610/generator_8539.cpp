#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);

    int N, M;
    vector<vector<int>> A;

    if (scenario == 0) {
        // Very small, edge-like
        N = 2;
        M = rnd.next(1, 3);
        A.assign(N, vector<int>(N));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                A[i][j] = rnd.next(0, 3);
    } else if (scenario == 1) {
        // Random small grid, many zeros
        N = rnd.next(3, 5);
        M = rnd.next(1, N + 3);
        A.assign(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (rnd.next(0, 99) < 40) A[i][j] = 0;
                else A[i][j] = rnd.next(1, 5);
            }
        }
    } else if (scenario == 2) {
        // Gradient pattern
        N = rnd.next(5, 8);
        M = rnd.next(3, 10);
        A.assign(N, vector<int>(N));
        int base = rnd.next(0, 3);
        int step = rnd.next(1, 4);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int val = base + step * (i + j);
                if (rnd.next(0, 99) < 20) val = 0; // some holes
                if (val > 100) val = 100;
                A[i][j] = val;
            }
        }
    } else if (scenario == 3) {
        // Extremes: mostly 0 or 100
        N = rnd.next(4, 8);
        M = rnd.next(5, 12);
        A.assign(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int t = rnd.next(0, 99);
                if (t < 15) A[i][j] = rnd.next(1, 99); // some random mids
                else if (t < 60) A[i][j] = 0;
                else A[i][j] = 100;
            }
        }
    } else {
        // Many cells >= 2 to create lots of clouds
        N = rnd.next(4, 8);
        M = rnd.next(8, 12);
        A.assign(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (rnd.next(0, 99) < 15) A[i][j] = 0;
                else A[i][j] = rnd.next(2, 10);
            }
        }
        // Tweak initial cloud region with diverse small values
        A[N-1][0] = rnd.next(0, 3);
        A[N-1][1] = rnd.next(1, 4);
        A[N-2][0] = rnd.next(0, 5);
        A[N-2][1] = rnd.next(2, 6);
    }

    // Generate commands
    vector<pair<int,int>> cmd;
    cmd.reserve(12);

    if (scenario == 2) {
        // Prefer diagonal directions
        for (int i = 0; i < M; ++i) {
            int d = 2 + 2 * rnd.next(0, 3); // 2,4,6,8
            int kind = rnd.next(0, 2);
            int s;
            if (kind == 0) s = rnd.next(1, N);
            else {
                int k = rnd.next(1, 6);
                s = k * N + rnd.next(0, N - 1);
                if (s > 50) s = (s % N) + 1;
            }
            cmd.push_back({d, s});
        }
    } else if (scenario == 4) {
        // Cyclic pattern of directions, with big and small s
        for (int i = 0; i < M; ++i) {
            int d = (i % 8) + 1;
            int s;
            if (i % 3 == 0) {
                int k = rnd.next(1, 6);
                s = k * N;
            } else if (i % 3 == 1) {
                s = rnd.next(1, N);
            } else {
                int k = rnd.next(1, 6);
                s = k * N + rnd.next(1, N);
            }
            if (s > 50) s = (s % N) + 1;
            if (s == 0) s = 1;
            cmd.push_back({d, s});
        }
    } else {
        // General random commands
        for (int i = 0; i < M; ++i) {
            int d = rnd.next(1, 8);
            int kind = rnd.next(0, 3);
            int s;
            if (kind == 0) {
                s = rnd.next(1, N);          // small
            } else if (kind == 1) {
                int k = rnd.next(1, 6);      // multiple of N
                s = k * N;
            } else {
                int k = rnd.next(1, 6);      // multiple plus offset
                s = k * N + rnd.next(0, N - 1);
            }
            if (s > 50) s = (s % N) + 1;
            if (s == 0) s = 1;
            cmd.push_back({d, s});
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; ++i)
        println(A[i]);

    for (int i = 0; i < M; ++i)
        println(cmd[i].first, cmd[i].second);

    return 0;
}
