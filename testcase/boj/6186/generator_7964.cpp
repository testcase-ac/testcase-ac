#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int R = rnd.next(1, 10);
    int C = rnd.next(1, 10);
    vector<string> grid(R, string(C, '.'));
    double continueProb = rnd.next(0.3, 1.0);
    double pairProb = rnd.next(0.0, 1.0);

    auto inBounds = [&](int i, int j) {
        return i >= 0 && i < R && j >= 0 && j < C;
    };
    auto cellOk = [&](int i, int j) {
        if (grid[i][j] != '.') return false;
        for (int di = -1; di <= 1; ++di) for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) continue;
            int ni = i + di, nj = j + dj;
            if (inBounds(ni, nj) && grid[ni][nj] == '#') return false;
        }
        return true;
    };
    auto pairOk = [&](int i1, int j1, int i2, int j2) {
        if (!inBounds(i1, j1) || !inBounds(i2, j2)) return false;
        if (grid[i1][j1] != '.' || grid[i2][j2] != '.') return false;
        for (int di = -1; di <= 1; ++di) for (int dj = -1; dj <= 1; ++dj) {
            int ni = i1 + di, nj = j1 + dj;
            if ((ni == i1 && nj == j1) || (ni == i2 && nj == j2)) continue;
            if (inBounds(ni, nj) && grid[ni][nj] == '#') return false;
        }
        for (int di = -1; di <= 1; ++di) for (int dj = -1; dj <= 1; ++dj) {
            int ni = i2 + di, nj = j2 + dj;
            if ((ni == i2 && nj == j2) || (ni == i1 && nj == j1)) continue;
            if (inBounds(ni, nj) && grid[ni][nj] == '#') return false;
        }
        return true;
    };

    struct Placement { vector<pair<int,int>> cells; };

    int maxIter = R * C;
    for (int iter = 0; iter < maxIter; ++iter) {
        if (rnd.next() >= continueProb) break;
        vector<Placement> singles, pairs;
        for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
            if (cellOk(i, j)) {
                singles.push_back({{{i, j}}});
            }
            if (pairOk(i, j, i, j+1)) {
                pairs.push_back({{{i, j}, {i, j+1}}});
            }
            if (pairOk(i, j, i+1, j)) {
                pairs.push_back({{{i, j}, {i+1, j}}});
            }
        }
        if (singles.empty() && pairs.empty()) break;
        bool wantPair = rnd.next() < pairProb;
        vector<Placement>* avail;
        if (wantPair && !pairs.empty()) avail = &pairs;
        else if (!wantPair && !singles.empty()) avail = &singles;
        else if (!pairs.empty()) avail = &pairs;
        else avail = &singles;
        auto &vec = *avail;
        int idx = rnd.next(0, (int)vec.size() - 1);
        for (auto &c : vec[idx].cells) {
            grid[c.first][c.second] = '#';
        }
    }

    bool has = false;
    for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j)
        if (grid[i][j] == '#') has = true;
    if (!has) {
        int i = rnd.next(0, R-1), j = rnd.next(0, C-1);
        grid[i][j] = '#';
    }

    println(R, C);
    for (int i = 0; i < R; ++i) {
        println(grid[i]);
    }
    return 0;
}
