#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size hyper-parameter
    int R, C;
    if (rnd.next(0, 1) == 0) {
        R = rnd.next(3, 5);
        C = rnd.next(3, 5);
    } else {
        R = rnd.next(6, 10);
        C = rnd.next(6, 10);
    }
    vector<pair<int,int>> path;
    pair<int,int> Mpos, Zpos;
    int L;
    // Generate a simple non-self-crossing path from M to Z with length >=5
    while (true) {
        int maxL = min(R * C, 12);
        if (rnd.next(0.0, 1.0) < 0.5) {
            L = rnd.next(5, min(maxL, 7));
        } else {
            L = rnd.next(8, maxL);
        }
        // pick M
        if (rnd.next(0.0, 1.0) < 0.3) {
            // on border
            if (rnd.next(0,1) == 0) {
                int c = rnd.next(1, C);
                int r = (rnd.next(0,1)==0 ? 1 : R);
                Mpos = {r, c};
            } else {
                int r = rnd.next(1, R);
                int c = (rnd.next(0,1)==0 ? 1 : C);
                Mpos = {r, c};
            }
        } else {
            Mpos = {rnd.next(1, R), rnd.next(1, C)};
        }
        path.clear();
        vector<vector<bool>> used(R+1, vector<bool>(C+1, false));
        path.push_back(Mpos);
        used[Mpos.first][Mpos.second] = true;
        bool fail = false;
        while ((int)path.size() < L) {
            auto [r, c] = path.back();
            vector<int> dirs = {0,1,2,3};
            shuffle(dirs.begin(), dirs.end());
            vector<int> cand;
            for (int d : dirs) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 1 || nr > R || nc < 1 || nc > C) continue;
                if (used[nr][nc]) continue;
                cand.push_back(d);
            }
            if (cand.empty()) { fail = true; break; }
            int d = rnd.any(cand);
            int nr = r + dr[d], nc = c + dc[d];
            path.emplace_back(nr, nc);
            used[nr][nc] = true;
        }
        if (fail || (int)path.size() != L) continue;
        Zpos = path.back();
        // Build blocks along internal nodes and check adjacency constraints
        int plen = path.size();
        int bsz = plen - 2;
        if (bsz < 3) continue; // need at least 3 internal to avoid removing near M/Z
        vector<pair<pair<int,int>,char>> blocks;
        bool badAdj = false;
        for (int i = 1; i+1 < plen; i++) {
            int r = path[i].first, c = path[i].second;
            auto [pr, pc] = path[i-1];
            auto [nr, nc] = path[i+1];
            int d1=-1, d2=-1;
            for (int d=0; d<4; d++) {
                if (pr + dr[d] == r && pc + dc[d] == c) d1 = d;
                if (r + dr[d] == nr && c + dc[d] == nc) d2 = d;
            }
            int id1 = (d1 + 2) % 4, id2 = d2;
            char blk;
            if ((id1==0 && id2==2) || (id1==2 && id2==0)) blk = '|';
            else if ((id1==1 && id2==3) || (id1==3 && id2==1)) blk = '-';
            else if ((id1==2 && id2==1)||(id1==1 && id2==2)) blk = '1';
            else if ((id1==0 && id2==1)||(id1==1 && id2==0)) blk = '2';
            else if ((id1==0 && id2==3)||(id1==3 && id2==0)) blk = '3';
            else if ((id1==2 && id2==3)||(id1==3 && id2==2)) blk = '4';
            else blk = '+';
            int bi = i-1;
            // adjacency check: only blocks[0] may touch M, only blocks[bsz-1] may touch Z
            if (abs(r - Mpos.first) + abs(c - Mpos.second) == 1 && bi != 0) badAdj = true;
            if (abs(r - Zpos.first) + abs(c - Zpos.second) == 1 && bi != bsz-1) badAdj = true;
            blocks.push_back({{r, c}, blk});
        }
        if (badAdj) continue;
        // Good path
        // Remove one internal block that's not adjacent to M or Z: indices 1..bsz-2
        int removeIdx = rnd.next(1, bsz-2);
        // Build grid
        vector<string> g(R+1, string(C+1, '.'));
        g[Mpos.first][Mpos.second] = 'M';
        g[Zpos.first][Zpos.second] = 'Z';
        for (int i = 0; i < bsz; i++) {
            int r = blocks[i].first.first, c = blocks[i].first.second;
            if (i == removeIdx) g[r][c] = '.';
            else g[r][c] = blocks[i].second;
        }
        // Output
        println(R, C);
        for (int i = 1; i <= R; i++) {
            string row;
            for (int j = 1; j <= C; j++) row.push_back(g[i][j]);
            println(row);
        }
        return 0;
    }
    return 0;
}
