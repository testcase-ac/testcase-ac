#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose dimensions: small (2–5), medium (6–12), or occasionally large (13–20)
    auto getSize = [&]() {
        int mode = rnd.next(0, 2);
        if (mode == 0) return rnd.next(2, 5);
        else if (mode == 1) return rnd.next(6, 12);
        else return rnd.next(13, 20);
    };
    int n = getSize();
    int m = getSize();
    vector<string> grid(n, string(m, '.'));

    // Hyper-parameter: cluster vs scatter of stars
    bool clusterStars = rnd.next(0, 1) == 1;
    if (clusterStars) {
        int clusters = rnd.next(1, 3);
        for (int c = 0; c < clusters; c++) {
            int ci = rnd.next(0, n - 1);
            int cj = rnd.next(0, m - 1);
            int maxr = max(1, min(n, m) / 3);
            int r = rnd.next(1, maxr);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    if (abs(i - ci) + abs(j - cj) <= r)
                        grid[i][j] = '*';
        }
    } else {
        int starPerc = rnd.next(5, 30);
        double starProb = starPerc / 100.0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (rnd.next() < starProb)
                    grid[i][j] = '*';
    }

    // Scatter pluses on remaining dots
    int plusPerc = rnd.next(5, 30);
    double plusProb = plusPerc / 100.0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == '.' && rnd.next() < plusProb)
                grid[i][j] = '+';

    // Ensure at least one '*' and one '+'
    bool hasStar = false, hasPlus = false;
    int countStars = 0;
    pair<int,int> onlyStarPos;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*') {
                hasStar = true;
                countStars++;
                onlyStarPos = {i, j};
            }
            if (grid[i][j] == '+') {
                hasPlus = true;
            }
        }
    }

    vector<pair<int,int>> positions;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            positions.emplace_back(i, j);

    if (!hasStar && !hasPlus) {
        // Assign both at two distinct positions
        shuffle(positions.begin(), positions.end());
        auto p1 = positions[0];
        auto p2 = positions[1];
        grid[p1.first][p1.second] = '*';
        grid[p2.first][p2.second] = '+';
    } else {
        if (!hasStar) {
            auto p = rnd.any(positions);
            grid[p.first][p.second] = '*';
            hasStar = true;
            onlyStarPos = p;
            countStars = 1;
        }
        if (!hasPlus) {
            pair<int,int> p;
            if (countStars == 1) {
                // avoid overwriting the only star
                vector<pair<int,int>> choices;
                for (auto &q : positions)
                    if (!(q.first == onlyStarPos.first && q.second == onlyStarPos.second))
                        choices.push_back(q);
                p = rnd.any(choices);
            } else {
                p = rnd.any(positions);
            }
            grid[p.first][p.second] = '+';
            hasPlus = true;
        }
    }

    // Output
    println(n, m);
    for (int i = 0; i < n; i++)
        println(grid[i]);
    return 0;
}
