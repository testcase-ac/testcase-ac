#include "testlib.h"
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 30, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read grid size
        int N = inf.readInt(1, 7, "N");
        inf.readEoln();

        // Read the grid
        vector<vector<int>> grid(N, vector<int>(N));
        for (int i = 0; i < N; i++) {
            vector<int> row = inf.readInts(N, -2, 4, "R");
            inf.readEoln();
            for (int j = 0; j < N; j++) {
                grid[i][j] = row[j];
            }
        }

        // Collect white cells and numbered black cells
        vector<pair<int,int>> whitePos;
        vector<vector<int>> idxOf(N, vector<int>(N, -1));
        struct NumCell { int i, j, k; vector<int> neigh; };
        vector<NumCell> nums;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int v = grid[i][j];
                if (v == -2) {
                    idxOf[i][j] = (int)whitePos.size();
                    whitePos.push_back({i, j});
                } else if (v >= 0) {
                    // numbered black cell
                    NumCell nc;
                    nc.i = i; nc.j = j; nc.k = v;
                    nums.push_back(nc);
                }
            }
        }

        int W = (int)whitePos.size();
        int M = (int)nums.size();

        // For each numbered cell, find adjacent white cells
        for (int idx = 0; idx < M; idx++) {
            int i = nums[idx].i, j = nums[idx].j;
            static const int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && ni < N && nj >= 0 && nj < N && grid[ni][nj] == -2) {
                    nums[idx].neigh.push_back(idxOf[ni][nj]);
                }
            }
            // Number cannot exceed available adjacent white cells
            ensuref(nums[idx].k <= (int)nums[idx].neigh.size(),
                    "Numbered cell at (%d,%d) has k=%d but only %d white neighbors",
                    i+1, j+1, nums[idx].k, (int)nums[idx].neigh.size());
        }

        // For each white cell, build adjacency to numbered cells
        vector<vector<int>> adjNums(W);
        for (int idx = 0; idx < M; idx++) {
            for (int w : nums[idx].neigh) {
                adjNums[w].push_back(idx);
            }
        }

        // For each white cell, build visibility list (other whites in straight line until a black)
        vector<vector<int>> visibility(W);
        for (int w = 0; w < W; w++) {
            int i = whitePos[w].first, j = whitePos[w].second;
            static const int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                while (ni >= 0 && ni < N && nj >= 0 && nj < N
                       && grid[ni][nj] == -2) {
                    int w2 = idxOf[ni][nj];
                    visibility[w].push_back(w2);
                    ni += dx[d];
                    nj += dy[d];
                }
            }
        }

        // Order white cells: those adjacent to numbered cells first (more constrained)
        vector<int> order(W);
        for (int i = 0; i < W; i++) order[i] = i;
        sort(order.begin(), order.end(), [&](int a, int b) {
            return adjNums[a].size() > adjNums[b].size();
        });
        vector<int> posIndex(W);
        for (int p = 0; p < W; p++) posIndex[order[p]] = p;

        // State for backtracking
        vector<bool> bulb(W, false);
        vector<int> lit_count(W, 0);
        vector<int> currCount(M, 0), undecided(M);
        for (int idx = 0; idx < M; idx++)
            undecided[idx] = (int)nums[idx].neigh.size();

        // Initial prune: for each numbered cell, k <= undecided
        for (int idx = 0; idx < M; idx++) {
            ensuref(nums[idx].k <= undecided[idx],
                    "Numbered cell at (%d,%d) cannot be satisfied: k=%d, possible=%d",
                    nums[idx].i+1, nums[idx].j+1, nums[idx].k, undecided[idx]);
        }

        // DFS to check existence of a solution
        function<bool(int)> dfs = [&](int pos) -> bool {
            if (pos == W) {
                // All decided: check all white cells are lit
                for (int w = 0; w < W; w++) {
                    if (lit_count[w] == 0)
                        return false;
                }
                // Number constraints are already enforced exactly when undecided==0
                return true;
            }
            int w = order[pos];

            // Option 1: place a bulb at w
            bool canPlace = true;
            // must not see another bulb
            for (int w2 : visibility[w]) {
                if (bulb[w2]) { canPlace = false; break; }
            }
            // must not exceed numbered neighbor counts
            if (canPlace) {
                for (int ni : adjNums[w]) {
                    if (currCount[ni] + 1 > nums[ni].k) {
                        canPlace = false; break;
                    }
                }
            }
            if (canPlace) {
                // apply placement
                bulb[w] = true;
                // update lighting
                vector<int> litUpd;
                lit_count[w]++; litUpd.push_back(w);
                for (int w2 : visibility[w]) {
                    lit_count[w2]++; litUpd.push_back(w2);
                }
                // update numbered neighbors
                for (int ni : adjNums[w]) {
                    currCount[ni]++;
                    undecided[ni]--;
                }
                // prune number constraints
                bool ok = true;
                for (int ni = 0; ni < M; ni++) {
                    if (currCount[ni] > nums[ni].k ||
                        currCount[ni] + undecided[ni] < nums[ni].k) {
                        ok = false; break;
                    }
                }
                if (ok && dfs(pos + 1)) return true;
                // backtrack
                bulb[w] = false;
                for (int u : litUpd) lit_count[u]--;
                for (int ni : adjNums[w]) {
                    currCount[ni]--;
                    undecided[ni]++;
                }
            }

            // Option 2: do not place a bulb
            // update undecided for numbered neighbors
            for (int ni : adjNums[w]) {
                undecided[ni]--;
            }
            // prune number constraints
            bool ok = true;
            for (int ni = 0; ni < M; ni++) {
                if (currCount[ni] > nums[ni].k ||
                    currCount[ni] + undecided[ni] < nums[ni].k) {
                    ok = false; break;
                }
            }
            // prune lighting possibility: w must be lit by future bulbs
            if (ok && lit_count[w] == 0) {
                bool canBeLit = false;
                for (int w2 : visibility[w]) {
                    if (posIndex[w2] > pos) {
                        canBeLit = true;
                        break;
                    }
                }
                if (!canBeLit) ok = false;
            }
            if (ok && dfs(pos + 1)) return true;
            // backtrack undecided
            for (int ni : adjNums[w]) {
                undecided[ni]++;
            }
            return false;
        };

        bool hasSol = dfs(0);
        ensuref(hasSol, "Test case %d has no valid solution", tc);
    }

    inf.readEof();
    return 0;
}
