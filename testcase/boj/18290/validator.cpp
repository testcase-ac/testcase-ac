#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    inf.readSpace();
    int K = inf.readInt(1, min(4, N * M), "K");
    inf.readEoln();

    // Read grid
    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readInts(M, -10000, 10000, "grid_row");
        inf.readEoln();
    }

    // Check that it is possible to select K non-adjacent cells
    // (as per statement: "항상 K개의 칸을 선택할 수 있는 경우만 입력으로 주어진다.")
    // We must check that there exists a selection of K cells such that no two are adjacent.

    // Since N, M <= 10 and K <= 4, we can brute-force all possible K-cell selections.
    int total_cells = N * M;
    vector<pair<int, int>> cells;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cells.emplace_back(i, j);

    bool found = false;
    vector<int> idx(total_cells);
    for (int i = 0; i < total_cells; ++i) idx[i] = i;

    // Generate all combinations of K cells
    vector<bool> select(total_cells, false);
    for (int i = 0; i < K; ++i) select[i] = true;
    do {
        vector<pair<int, int>> chosen;
        for (int i = 0; i < total_cells; ++i) {
            if (select[i]) chosen.push_back(cells[i]);
        }
        // Check if any two are adjacent
        bool ok = true;
        for (int a = 0; a < K && ok; ++a) {
            for (int b = a + 1; b < K && ok; ++b) {
                int r1 = chosen[a].first, c1 = chosen[a].second;
                int r2 = chosen[b].first, c2 = chosen[b].second;
                if (abs(r1 - r2) + abs(c1 - c2) == 1) {
                    ok = false;
                }
            }
        }
        if (ok) {
            found = true;
            break;
        }
    } while (prev_permutation(select.begin(), select.end()));

    ensuref(found, "It is not possible to select %d non-adjacent cells in the given grid (N=%d, M=%d)", K, N, M);

    inf.readEof();
}
