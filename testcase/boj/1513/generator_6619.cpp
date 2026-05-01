#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 3);
    int N, M, C;
    vector<pair<int,int>> arc;

    if (type == 0) {
        // No arcades
        N = rnd.next(1, 10);
        M = rnd.next(1, 10);
        C = 0;
    } else if (type == 1) {
        // Small grid, random arcades inside
        N = rnd.next(2, 10);
        M = rnd.next(2, 10);
        int maxC = min(N * M - 2, 8);
        C = rnd.next(1, maxC);
        vector<pair<int,int>> cells;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                if (!(i == 1 && j == 1) && !(i == N && j == M))
                    cells.emplace_back(i, j);
        shuffle(cells.begin(), cells.end());
        arc.assign(cells.begin(), cells.begin() + C);
    } else if (type == 2) {
        // Force arcades at start and end, plus some extras
        N = rnd.next(2, 10);
        M = rnd.next(2, 10);
        int extraMax = N * M - 2;
        int extra = rnd.next(0, min(3, extraMax));
        C = extra + 2;
        // base positions
        arc.emplace_back(1, 1);
        arc.emplace_back(N, M);
        vector<pair<int,int>> cells;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                if (!((i == 1 && j == 1) || (i == N && j == M)))
                    cells.emplace_back(i, j);
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < extra; i++)
            arc.push_back(cells[i]);
    } else {
        // Large grid, random few arcades
        N = rnd.next(30, 50);
        M = rnd.next(30, 50);
        int maxC = min(N * M - 2, 12);
        C = rnd.next(0, maxC);
        vector<pair<int,int>> cells;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                if (!(i == 1 && j == 1) && !(i == N && j == M))
                    cells.emplace_back(i, j);
        shuffle(cells.begin(), cells.end());
        arc.assign(cells.begin(), cells.begin() + C);
    }

    // Shuffle the arcade order to assign IDs
    if (C > 1) {
        shuffle(arc.begin(), arc.end());
    }

    // Output
    println(N, M, C);
    for (int i = 0; i < C; i++) {
        println(arc[i].first, arc[i].second);
    }
    return 0;
}
