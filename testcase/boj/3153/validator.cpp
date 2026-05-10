#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R, S
    int R = inf.readInt(1, 100, "R");
    inf.readSpace();
    int S = inf.readInt(1, 100, "S");
    inf.readEoln();

    vector<string> grid(R);
    int tower_cnt = 0, clone_cnt = 0;
    for (int i = 0; i < R; ++i) {
        grid[i] = inf.readLine("[A-Za-z#\\.]{"+to_string(S)+"}", "map row");
        ensuref((int)grid[i].size() == S, "Row %d: Expected %d columns, got %d", i+1, S, (int)grid[i].size());
        for (int j = 0; j < S; ++j) {
            char c = grid[i][j];
            ensuref(
                c == 'T' || c == 'n' || c == '#' || c == '.',
                "Invalid character '%c' at row %d, col %d", c, i+1, j+1
            );
            if (c == 'T') ++tower_cnt;
            if (c == 'n') ++clone_cnt;
        }
    }

    // There must be at least one tower and at least one clone for the problem to be meaningful.
    ensuref(tower_cnt >= 1, "There must be at least one tower (T), found %d", tower_cnt);
    ensuref(clone_cnt >= 1, "There must be at least one clone (n), found %d", clone_cnt);

    // Check that the answer always exists (as per statement).
    // We must check that there exists a way to assign directions to all towers so that:
    //  - All clones are hit by at least one cannonball
    //  - No tower is destroyed (i.e., no cannonball hits any tower)
    //  - All cannonballs are fired simultaneously, each tower picks one of 4 possible direction pairs

    // For each tower, precompute the 4 possible firing options.
    // For each option, compute the set of clones hit, and check if any tower is hit (invalid option).
    // Then, do a search over all combinations (if number of towers is small), or use a greedy covering if possible.

    // Since R,S <= 100, but number of towers can be up to 10,000, we cannot brute-force all combinations.
    // But the statement guarantees that the answer always exists, so we can check that for each clone,
    // there is at least one tower and at least one direction pair such that the clone is hit and no tower is destroyed.

    // For each tower, store its position
    vector<pair<int,int>> towers;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < S; ++j)
            if (grid[i][j] == 'T')
                towers.emplace_back(i, j);

    // For each tower, for each direction pair, store:
    //   - set of clones hit
    //   - whether any tower is destroyed (invalid option)
    // Direction pairs:
    // 0: left+down
    // 1: down+right
    // 2: right+up
    // 3: up+left
    const int DIRS[4][2][2] = {
        { {0,-1}, {1,0} }, // left, down
        { {1,0}, {0,1} },  // down, right
        { {0,1}, {-1,0} }, // right, up
        { {-1,0}, {0,-1} } // up, left
    };

    // Map from clone position to index
    vector<pair<int,int>> clones;
    vector<vector<int>> clone_idx(R, vector<int>(S, -1));
    int idx = 0;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < S; ++j)
            if (grid[i][j] == 'n') {
                clones.emplace_back(i, j);
                clone_idx[i][j] = idx++;
            }

    int T = (int)towers.size();
    int N = (int)clones.size();

    // For each tower, for each direction pair, store:
    //   - set of clones hit (as bitset)
    //   - valid (no tower is destroyed)
    vector<vector<vector<int>>> tower_hits(T, vector<vector<int>>(4)); // [tower][dir] = vector of clone indices
    vector<vector<bool>> tower_valid(T, vector<bool>(4, true)); // [tower][dir] = true if no tower is destroyed

    for (int t = 0; t < T; ++t) {
        int x = towers[t].first, y = towers[t].second;
        for (int d = 0; d < 4; ++d) {
            set<pair<int,int>> visited;
            bool valid = true;
            vector<int> hits;
            for (int k = 0; k < 2; ++k) {
                int dx = DIRS[d][k][0], dy = DIRS[d][k][1];
                int nx = x + dx, ny = y + dy;
                while (0 <= nx && nx < R && 0 <= ny && ny < S) {
                    char c = grid[nx][ny];
                    if (c == '#') break; // wall, cannonball destroyed
                    if (c == 'T') { valid = false; break; } // tower destroyed, invalid
                    if (c == 'n') {
                        if (!visited.count({nx, ny})) {
                            hits.push_back(clone_idx[nx][ny]);
                            visited.insert({nx, ny});
                        }
                    }
                    nx += dx; ny += dy;
                }
                if (!valid) break;
            }
            tower_valid[t][d] = valid;
            if (valid) tower_hits[t][d] = hits;
        }
    }

    // For each clone, check that there is at least one tower and one direction such that:
    //  - the clone is hit
    //  - the direction is valid (no tower destroyed)
    for (int c = 0; c < N; ++c) {
        bool can_be_hit = false;
        for (int t = 0; t < T; ++t) {
            for (int d = 0; d < 4; ++d) {
                if (!tower_valid[t][d]) continue;
                for (int idx : tower_hits[t][d]) {
                    if (idx == c) {
                        can_be_hit = true;
                        goto next_clone;
                    }
                }
            }
        }
        next_clone:
        ensuref(can_be_hit, "Clone at (%d,%d) cannot be hit by any valid cannonball", clones[c].first+1, clones[c].second+1);
    }

    // Additionally, check that there is at least one valid direction for each tower
    for (int t = 0; t < T; ++t) {
        bool has_valid = false;
        for (int d = 0; d < 4; ++d) {
            if (tower_valid[t][d]) has_valid = true;
        }
        ensuref(has_valid, "Tower at (%d,%d) has no valid firing direction", towers[t].first+1, towers[t].second+1);
    }

    inf.readEof();
}
