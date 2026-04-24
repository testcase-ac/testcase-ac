#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read N, M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read grid
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
        // read whole line, then check
        string row = inf.readLine("[^]+", "row");
        ensuref((int)row.size() == M,
                "Each row must have exactly M=%d characters, but row %d has %d",
                M, i, (int)row.size());
        for (int j = 0; j < M; j++) {
            char c = row[j];
            ensuref(c >= 'A' && c <= 'Z',
                    "Invalid character '%c' at row %d, col %d: must be A-Z", c, i, j);
        }
        grid[i] = row;
    }
    // Top-left must not be 'X'
    ensuref(grid[0][0] != 'X',
            "Top-left codel must not be black (X), but is X");

    // Build connected components of non-'X' cells
    vector<vector<int>> comp_id(N, vector<int>(M, -1));
    vector<vector<pair<int,int>>> comps;
    int dr4[4] = { -1, 1, 0, 0 };
    int dc4[4] = { 0, 0, -1, 1 };
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] != 'X' && comp_id[i][j] < 0) {
                int cid = comps.size();
                comps.emplace_back();
                // BFS
                queue<pair<int,int>> q;
                q.push({i,j});
                comp_id[i][j] = cid;
                while (!q.empty()) {
                    auto [r,c] = q.front(); q.pop();
                    comps[cid].push_back({r,c});
                    for (int d = 0; d < 4; d++) {
                        int nr = r + dr4[d], nc = c + dc4[d];
                        if (nr >= 0 && nr < N && nc >= 0 && nc < M
                            && grid[nr][nc] != 'X' 
                            && comp_id[nr][nc] < 0) {
                            comp_id[nr][nc] = cid;
                            q.push({nr,nc});
                        }
                    }
                }
            }
        }
    }
    int C = comps.size();
    ensuref(C > 0, "There must be at least one non-black codel");

    // Precompute for each component, each DP (0=right,1=down,2=left,3=up), each CC (0=left,1=right)
    // the selected codel (r,c)
    // Directions: 0=right(dy=0,dx=1), 1=down(dy=1,dx=0), 2=left(dy=0,dx=-1),3=up(dy=-1,dx=0)
    int drDP[4] = {0, 1, 0, -1};
    int dcDP[4] = {1, 0, -1, 0};
    // best_codel[cid][dp][cc] = pair(r,c)
    vector<array<array<pair<int,int>,2>,4>> best_codel(C);

    for (int cid = 0; cid < C; cid++) {
        auto &cells = comps[cid];
        for (int dp = 0; dp < 4; dp++) {
            // find the extreme coordinate for dp
            int extreme1;
            if (dp == 0) { // right: max col
                extreme1 = INT_MIN;
                for (auto &p : cells) extreme1 = max(extreme1, p.second);
            } else if (dp == 2) { // left: min col
                extreme1 = INT_MAX;
                for (auto &p : cells) extreme1 = min(extreme1, p.second);
            } else if (dp == 1) { // down: max row
                extreme1 = INT_MIN;
                for (auto &p : cells) extreme1 = max(extreme1, p.first);
            } else { // dp==3 up: min row
                extreme1 = INT_MAX;
                for (auto &p : cells) extreme1 = min(extreme1, p.first);
            }
            for (int cc = 0; cc < 2; cc++) {
                // among those with coordinate == extreme1, pick by cc
                pair<int,int> chosen = {-1,-1};
                if (dp == 0) { 
                    // right: choose among col==extreme1, cc=0->min row, cc=1->max row
                    int best = (cc==0? INT_MAX : INT_MIN);
                    for (auto &p : cells) if (p.second == extreme1) {
                        if ((cc==0 && p.first < best) || (cc==1 && p.first > best)) {
                            best = p.first; chosen = p;
                        }
                    }
                } else if (dp == 2) {
                    // left: col==extreme1, cc=0->max row, cc=1->min row
                    int best = (cc==0? INT_MIN : INT_MAX);
                    for (auto &p : cells) if (p.second == extreme1) {
                        if ((cc==0 && p.first > best) || (cc==1 && p.first < best)) {
                            best = p.first; chosen = p;
                        }
                    }
                } else if (dp == 1) {
                    // down: row==extreme1, cc=0->max col, cc=1->min col
                    int best = (cc==0? INT_MIN : INT_MAX);
                    for (auto &p : cells) if (p.first == extreme1) {
                        if ((cc==0 && p.second > best) || (cc==1 && p.second < best)) {
                            best = p.second; chosen = p;
                        }
                    }
                } else { // up
                    // row==extreme1, cc=0->min col, cc=1->max col
                    int best = (cc==0? INT_MAX : INT_MIN);
                    for (auto &p : cells) if (p.first == extreme1) {
                        if ((cc==0 && p.second < best) || (cc==1 && p.second > best)) {
                            best = p.second; chosen = p;
                        }
                    }
                }
                ensuref(chosen.first >= 0,
                        "Unable to pick a codel for component %d, dp=%d, cc=%d", cid, dp, cc);
                best_codel[cid][dp][cc] = chosen;
            }
        }
    }

    // Simulate execution to ensure termination (no infinite loop)
    vector<vector<vector<bool>>> seen(
        C, vector<vector<bool>>(4, vector<bool>(2, false)));
    int cur_comp = comp_id[0][0];
    int DP = 0; // 0=right
    int CC = 0; // 0=left

    while (true) {
        if (seen[cur_comp][DP][CC]) {
            ensuref(false,
                    "Non-terminating program detected: cycle at component %d, DP=%d, CC=%d",
                    cur_comp, DP, CC);
        }
        seen[cur_comp][DP][CC] = true;
        bool moved = false;
        int try_dp = DP, try_cc = CC;
        for (int t = 0; t < 8; t++) {
            auto [r, c] = best_codel[cur_comp][try_dp][try_cc];
            int nr = r + drDP[try_dp];
            int nc = c + dcDP[try_dp];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != 'X') {
                // can move
                cur_comp = comp_id[nr][nc];
                DP = try_dp;
                CC = try_cc;
                moved = true;
                break;
            }
            // update for next attempt
            if (t % 2 == 0) {
                try_cc ^= 1;
            } else {
                try_dp = (try_dp + 1) % 4;
            }
        }
        if (!moved) {
            // terminated properly
            break;
        }
    }

    inf.readEof();
    return 0;
}
