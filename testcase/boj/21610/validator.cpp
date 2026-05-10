#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(2, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read initial water amounts A[r][c]
    vector<vector<int>> A(N, vector<int>(N));
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            A[r][c] = inf.readInt(0, 100, "A_rc");
            if (c + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    struct Move {
        int d;
        int s;
    };
    vector<Move> moves(M);
    for (int i = 0; i < M; ++i) {
        moves[i].d = inf.readInt(1, 8, "d_i");
        inf.readSpace();
        moves[i].s = inf.readInt(1, 50, "s_i");
        inf.readEoln();
    }

    // Simulate to ensure global assumptions (e.g., no overflow, valid behavior)
    // Directions: 1←, 2↖, 3↑, 4↗, 5→, 6↘, 7↓, 8↙
    int dr[9] = {0, 0,-1,-1,-1, 0, 1, 1, 1};
    int dc[9] = {0,-1,-1, 0, 1, 1, 1, 0,-1};
    int ddr[4] = {-1,-1,1,1};
    int ddc[4] = {-1,1,-1,1};

    // initial clouds: (N,1),(N,2),(N-1,1),(N-1,2) -> 0-based: (N-1,0),(N-1,1),(N-2,0),(N-2,1)
    vector<pair<int,int>> clouds;
    clouds.reserve(N * N);
    if (N >= 2) {
        clouds.push_back({N-1, 0});
        clouds.push_back({N-1, 1});
        clouds.push_back({N-2, 0});
        clouds.push_back({N-2, 1});
    }

    vector<vector<bool>> cloudHere(N, vector<bool>(N, false));
    vector<vector<bool>> prevCloud(N, vector<bool>(N, false));

    for (int i = 0; i < M; ++i) {
        int d = moves[i].d;
        int s = moves[i].s % N; // wrapping on torus, effective steps

        // Move clouds
        for (auto &p : clouds) {
            int r = p.first;
            int c = p.second;
            int nr = (r + dr[d] * s) % N;
            int nc = (c + dc[d] * s) % N;
            if (nr < 0) nr += N;
            if (nc < 0) nc += N;
            p.first = nr;
            p.second = nc;
        }

        // Step 2: rain
        for (auto &p : clouds) {
            A[p.first][p.second] += 1;
        }

        // Mark positions where clouds were (for step 5 condition)
        for (int r = 0; r < N; ++r)
            for (int c = 0; c < N; ++c)
                prevCloud[r][c] = false;
        for (auto &p : clouds) {
            prevCloud[p.first][p.second] = true;
        }

        // Step 3: clouds disappear: we will rebuild later
        // Step 4: water copy bug
        vector<pair<int,int>> increasedCells = clouds;
        for (auto &p : increasedCells) {
            int r = p.first;
            int c = p.second;
            int cnt = 0;
            for (int k = 0; k < 4; ++k) {
                int nr = r + ddr[k];
                int nc = c + ddc[k];
                if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
                if (A[nr][nc] > 0) cnt++;
            }
            A[r][c] += cnt;
        }

        // Step 5: form new clouds on cells with A[r][c] >= 2 and not in prevCloud
        clouds.clear();
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (!prevCloud[r][c] && A[r][c] >= 2) {
                    clouds.push_back({r,c});
                    A[r][c] -= 2;
                }
            }
        }
    }

    // Compute final sum, ensure it fits in 64-bit (it definitely should)
    long long sum = 0;
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            sum += A[r][c];

    // No explicit bound is given for the answer, but we ensure non-negative
    ensuref(sum >= 0, "Final water sum is negative, which should be impossible.");

    inf.readEof();
}
