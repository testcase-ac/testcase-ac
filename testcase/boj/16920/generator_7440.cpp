#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid dimensions
    int N = rnd.next(3, 12);
    int M = rnd.next(3, 12);

    // Number of players
    int maxP = min(9, (N * M) / 3);
    int P = rnd.next(1, max(1, maxP));

    // Generate expansion speeds with varied distribution
    vector<int> S(P);
    for (int i = 0; i < P; i++) {
        int hi = rnd.next(1, 10);
        int t = rnd.next(-1, 1); // skew low, uniform, or skew high
        S[i] = rnd.wnext(hi, t);
        if (S[i] < 1) S[i] = 1;
    }

    // Initialize grid with dots
    vector<string> grid(N, string(M, '.'));

    // Place walls with random density up to ~30%
    int wPercent = rnd.next(0, 30);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (rnd.next(0, 99) < wPercent) {
                grid[i][j] = '#';
            }
        }
    }

    // Collect empty cells and ensure enough for players
    vector<pair<int,int>> empties;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (grid[i][j] == '.')
                empties.emplace_back(i, j);

    if ((int)empties.size() < P) {
        // Too many walls; clear walls
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (grid[i][j] == '#')
                    grid[i][j] = '.';
        empties.clear();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                empties.emplace_back(i, j);
    }

    // Decide number of starting castles per player (1 or 2)
    vector<int> castles(P);
    int remainPlayers = P;
    int remainEmpties = empties.size();
    for (int i = 0; i < P; i++) {
        int minC = 1;
        int maxC = min(2, remainEmpties - (remainPlayers - 1));
        castles[i] = rnd.next(minC, maxC);
        remainEmpties -= castles[i];
        remainPlayers--;
    }

    // Shuffle empty cells and assign castles
    shuffle(empties.begin(), empties.end());
    int idx = 0;
    for (int i = 0; i < P; i++) {
        for (int c = 0; c < castles[i]; c++) {
            auto [r, c2] = empties[idx++];
            grid[r][c2] = char('1' + i);
        }
    }

    // Output
    println(N, M, P);
    println(S);
    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i].c_str());
    }

    return 0;
}
