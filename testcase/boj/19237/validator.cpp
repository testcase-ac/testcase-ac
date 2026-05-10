#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, k
    int N = inf.readInt(2, 20, "N");
    inf.readSpace();
    int M = inf.readInt(2, N*N, "M");
    inf.readSpace();
    int k = inf.readInt(1, 1000, "k");
    inf.readEoln();

    // 2. Read grid and validate
    vector<vector<int>> grid(N, vector<int>(N));
    set<int> shark_nums;
    int shark_cnt = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            grid[i][j] = inf.readInt(0, M, "grid[i][j]");
            if (j < N-1) inf.readSpace();
            if (grid[i][j] != 0) {
                ++shark_cnt;
                ensuref(grid[i][j] >= 1 && grid[i][j] <= M, "Shark number at (%d,%d) is %d, out of range 1..M", i+1, j+1, grid[i][j]);
                ensuref(!shark_nums.count(grid[i][j]), "Duplicate shark number %d at (%d,%d)", grid[i][j], i+1, j+1);
                shark_nums.insert(grid[i][j]);
            }
        }
        inf.readEoln();
    }
    ensuref(shark_cnt == M, "Number of sharks on grid is %d, but M = %d", shark_cnt, M);
    // All shark numbers 1..M must be present
    for (int i = 1; i <= M; ++i) {
        ensuref(shark_nums.count(i), "Shark number %d is missing from the grid", i);
    }

    // 3. Read initial directions
    vector<int> init_dir(M+1, -1); // 1-based shark number
    for (int i = 1; i <= M; ++i) {
        init_dir[i] = inf.readInt(1, 4, "init_dir[i]");
        if (i < M) inf.readSpace();
    }
    inf.readEoln();

    // 4. Read priority tables
    // For each shark 1..M, 4 lines, each line 4 ints (directions 1..4, permutation)
    // priority[shark][dir][0..3] = direction
    for (int s = 1; s <= M; ++s) {
        for (int d = 1; d <= 4; ++d) {
            vector<int> prio = inf.readInts(4, 1, 4, "priority");
            inf.readEoln();
            // Validate that prio is a permutation of 1..4
            vector<int> check = prio;
            sort(check.begin(), check.end());
            for (int x = 0; x < 4; ++x) {
                ensuref(check[x] == x+1, "Priority for shark %d, dir %d is not a permutation of 1..4", s, d);
            }
        }
    }

    // 5. Validate: "맨 처음에는 각 상어마다 인접한 빈 칸이 존재한다."
    // For each shark, check that at least one adjacent cell is empty
    const int dx[5] = {0, -1, 1, 0, 0}; // 1:up, 2:down, 3:left, 4:right
    const int dy[5] = {0, 0, 0, -1, 1};
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
        if (grid[i][j] != 0) {
            bool found = false;
            for (int dir = 1; dir <= 4; ++dir) {
                int ni = i + dx[dir], nj = j + dy[dir];
                if (ni >= 0 && ni < N && nj >= 0 && nj < N) {
                    if (grid[ni][nj] == 0) found = true;
                }
            }
            ensuref(found, "Shark at (%d,%d) has no adjacent empty cell at start", i+1, j+1);
        }
    }

    inf.readEof();
}
