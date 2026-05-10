#include "testlib.h"
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// Directions for fish: 1..8 mapped to 0..7 index
// Problem order: 1:←,2:↖,3:↑,4:↗,5:→,6:↘,7:↓,8:↙
// We'll store as dx,dy arrays in this order.
int fdx[8] = {0,-1,-1,-1,0,1,1,1};
int fdy[8] = {-1,-1,0,1,1,1,0,-1};

// Shark directions: up, left, down, right in that lexicographic order
int sdx[4] = {-1,0,1,0};
int sdy[4] = {0,-1,0,1};

// simulate the whole process to verify total fish count bound
void simulate(int M, int S,
              const vector<tuple<int,int,int>>& fishes,
              int sx, int sy)
{
    // fish[x][y][d]: number of fish at (x,y) with direction d (0..7)
    static int fish[4][4][8];
    static int nextFish[4][4][8];
    static int smell[4][4];

    memset(fish, 0, sizeof(fish));
    memset(smell, 0, sizeof(smell));

    for (auto &t : fishes) {
        int x,y,d;
        tie(x,y,d) = t;
        // convert to 0-based
        fish[x-1][y-1][d-1]++;
    }
    int sharkX = sx-1, sharkY = sy-1;

    auto inside = [](int x, int y)->bool{
        return 0 <= x && x < 4 && 0 <= y && y < 4;
    };

    for (int step = 0; step < S; ++step) {
        // 1) copy magic: remember current fish as "copies"
        int copyFish[4][4][8];
        memcpy(copyFish, fish, sizeof(fish));

        // 2) fish move
        memset(nextFish, 0, sizeof(nextFish));
        for (int x=0;x<4;++x) for (int y=0;y<4;++y) {
            for (int d=0; d<8; ++d) {
                int cnt = fish[x][y][d];
                if (!cnt) continue;
                int nd = d;
                bool moved = false;
                for (int k=0;k<8;++k) {
                    int nx = x + fdx[nd];
                    int ny = y + fdy[nd];
                    if (inside(nx,ny) &&
                        !(nx==sharkX && ny==sharkY) &&
                        smell[nx][ny]==0) {
                        nextFish[nx][ny][nd] += cnt;
                        moved = true;
                        break;
                    }
                    nd = (nd + 7) % 8; // rotate 45 deg CCW
                }
                if (!moved) {
                    nextFish[x][y][d] += cnt;
                }
            }
        }
        memcpy(fish, nextFish, sizeof(fish));

        // 3) shark moves 3 steps, choose best path
        int bestEat = -1;
        int bestDirSeq[3] = {0,0,0};
        int bestX = sharkX, bestY = sharkY;

        // try all 4^3 = 64 sequences
        for (int a=0;a<4;++a)
        for (int b=0;b<4;++b)
        for (int c=0;c<4;++c) {
            int dirs[3] = {a,b,c};
            int cx = sharkX, cy = sharkY;
            bool ok = true;
            bool vis[4][4];
            memset(vis, 0, sizeof(vis));
            int eat = 0;
            for (int i=0;i<3;++i) {
                cx += sdx[dirs[i]];
                cy += sdy[dirs[i]];
                if (!inside(cx,cy)) {
                    ok = false;
                    break;
                }
                if (!vis[cx][cy]) {
                    vis[cx][cy] = true;
                    int cellFish = 0;
                    for (int d=0; d<8; ++d) cellFish += fish[cx][cy][d];
                    eat += cellFish;
                }
            }
            if (!ok) continue;
            if (eat > bestEat) {
                bestEat = eat;
                bestDirSeq[0]=a; bestDirSeq[1]=b; bestDirSeq[2]=c;
                bestX = cx; bestY = cy;
            }
            // if tie, lexicographically smaller dir sequence wins
            else if (eat == bestEat) {
                bool better = false;
                for (int i=0;i<3;++i) {
                    if (dirs[i] < bestDirSeq[i]) { better = true; break; }
                    if (dirs[i] > bestDirSeq[i]) break;
                }
                if (better) {
                    bestDirSeq[0]=a; bestDirSeq[1]=b; bestDirSeq[2]=c;
                    bestX = cx; bestY = cy;
                }
            }
        }

        // apply best path: remove fish and set smell
        int cx = sharkX, cy = sharkY;
        for (int i=0;i<3;++i) {
            cx += sdx[bestDirSeq[i]];
            cy += sdy[bestDirSeq[i]];
            int removed = 0;
            for (int d=0;d<8;++d) {
                removed += fish[cx][cy][d];
                fish[cx][cy][d] = 0;
            }
            if (removed > 0) {
                smell[cx][cy] = 3; // will decrement to 2 right after
            }
        }
        sharkX = bestX;
        sharkY = bestY;

        // 4) decrease smell ages, remove those of age 0
        for (int x=0;x<4;++x) for (int y=0;y<4;++y) {
            if (smell[x][y] > 0) smell[x][y]--;
        }

        // 5) complete copy: add copyFish
        for (int x=0;x<4;++x) for (int y=0;y<4;++y)
            for (int d=0;d<8;++d)
                fish[x][y][d] += copyFish[x][y][d];

        // after each step, enforce fish <= 1,000,000
        long long total = 0;
        for (int x=0;x<4;++x) for (int y=0;y<4;++y)
            for (int d=0;d<8;++d)
                total += fish[x][y][d];
        ensuref(total <= 1000000LL,
                "Total fish count after step %d exceeds 1,000,000: %lld",
                step+1, total);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case problem (BOJ-style)
    int M = inf.readInt(1, 10, "M");
    inf.readSpace();
    int S = inf.readInt(1, 100, "S");
    inf.readEoln();

    vector<tuple<int,int,int>> fishes;
    fishes.reserve(M);

    for (int i = 0; i < M; ++i) {
        int fx = inf.readInt(1, 4, "f_x");
        inf.readSpace();
        int fy = inf.readInt(1, 4, "f_y");
        inf.readSpace();
        int d  = inf.readInt(1, 8, "d");
        inf.readEoln();
        fishes.emplace_back(fx, fy, d);
    }

    int sx = inf.readInt(1, 4, "s_x");
    inf.readSpace();
    int sy = inf.readInt(1, 4, "s_y");
    inf.readEoln();

    // Simulate to verify global guarantee: fish count never exceeds 1e6
    simulate(M, S, fishes, sx, sy);

    inf.readEof();
}
