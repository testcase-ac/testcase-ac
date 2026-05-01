#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 3);
    int N;

    if (scenario == 0) N = rnd.next(2, 3);
    else if (scenario == 1) N = rnd.next(3, 6);
    else if (scenario == 2) N = rnd.next(4, 8);
    else N = rnd.next(7, 10);

    int mType = rnd.next(0, 2);
    int M;
    if (mType == 0) M = rnd.next(2, 5);
    else if (mType == 1) M = rnd.next(6, 10);
    else M = rnd.next(11, 20);

    vector<vector<int>> a(N, vector<int>(N, 1));
    vector<vector<bool>> onPath(N, vector<bool>(N, false));

    // Backbone path: top row then last column
    for (int j = 0; j < N; ++j) onPath[0][j] = true;
    for (int i = 1; i < N; ++i) onPath[i][N - 1] = true;

    // Collect off-path cells for candidate
    vector<pair<int,int>> offPath;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (!onPath[i][j])
                offPath.push_back({i, j});

    // There is always at least one off-path cell when N >= 2
    pair<int,int> cand = rnd.any(offPath);
    int cr = cand.first;
    int cc = cand.second;
    a[cr][cc] = 0; // new bridge candidate cliff

    auto nearCand = [&](int i, int j) {
        return (abs(i - cr) + abs(j - cc) == 1);
    };

    // Scenario-specific parameters
    int zeroExtra = 0;
    int numBridges = 0;
    bool makeVerticalWall = false;
    bool makeHorizontalWall = false;

    if (scenario == 0) {
        zeroExtra = rnd.next(0, 1);
        numBridges = rnd.next(0, 1);
    } else if (scenario == 1) {
        zeroExtra = rnd.next(0, max(1, N / 2));
        numBridges = rnd.next(0, max(1, N / 2));
        if (N >= 4 && rnd.next(0, 1)) makeVerticalWall = true;
    } else if (scenario == 2) {
        zeroExtra = rnd.next(max(1, N / 3), N);
        numBridges = rnd.next(0, N);
        if (N >= 4) {
            makeVerticalWall = true;
            if (rnd.next(0, 1)) makeHorizontalWall = true;
        }
    } else {
        zeroExtra = rnd.next(0, N);
        numBridges = rnd.next(max(1, N / 2), N + max(1, N / 2));
        if (N >= 4) {
            if (rnd.next(0, 1)) makeVerticalWall = true;
            if (rnd.next(0, 1)) makeHorizontalWall = true;
        }
    }

    // Random extra cliffs (zeros), keeping backbone and candidate safe
    int placed = 0;
    int tries = 0;
    int maxTries = zeroExtra * 10 + 100;
    while (placed < zeroExtra && tries++ < maxTries) {
        int i = rnd.next(0, N - 1);
        int j = rnd.next(0, N - 1);
        if (onPath[i][j]) continue;
        if (i == cr && j == cc) continue;
        if (nearCand(i, j)) continue;
        if (a[i][j] != 1) continue; // don't change existing bridges or cliffs here
        a[i][j] = 0;
        placed++;
    }

    // Optional vertical wall of cliffs
    if (makeVerticalWall) {
        int c = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i) {
            if (onPath[i][c]) continue;
            if (i == cr && c == cc) continue;
            if (nearCand(i, c)) continue;
            a[i][c] = 0;
        }
    }

    // Optional horizontal wall of cliffs
    if (makeHorizontalWall) {
        int r = rnd.next(0, N - 1);
        for (int j = 0; j < N; ++j) {
            if (onPath[r][j]) continue;
            if (r == cr && j == cc) continue;
            if (nearCand(r, j)) continue;
            a[r][j] = 0;
        }
    }

    // Existing periodic bridges (values >= 2), not on backbone, not at candidate,
    // not adjacent to candidate, and not at cliff intersections
    int bPlaced = 0;
    tries = 0;
    int limit = numBridges * 20 + 200;
    while (bPlaced < numBridges && tries++ < limit) {
        int i = rnd.next(0, N - 1);
        int j = rnd.next(0, N - 1);
        if (onPath[i][j]) continue;
        if (i == cr && j == cc) continue;
        if (nearCand(i, j)) continue;

        // Check if placing a bridge here would be at a cliff intersection
        auto isCliff = [&](int x, int y) {
            return (a[x][y] == 0 || a[x][y] >= 2);
        };

        bool upCliff = (i > 0) && isCliff(i - 1, j);
        bool downCliff = (i + 1 < N) && isCliff(i + 1, j);
        bool leftCliff = (j > 0) && isCliff(i, j - 1);
        bool rightCliff = (j + 1 < N) && isCliff(i, j + 1);

        if (upCliff && downCliff && leftCliff && rightCliff)
            continue; // can't place bridge at intersection

        int rangeType = rnd.next(0, 2);
        int T;
        if (rangeType == 0) T = rnd.next(2, 5);
        else if (rangeType == 1) T = rnd.next(6, 10);
        else T = rnd.next(11, 20);

        a[i][j] = T;
        bPlaced++;
    }

    // Ensure start and end are land
    a[0][0] = 1;
    a[N-1][N-1] = 1;

    println(N, M);
    for (int i = 0; i < N; ++i) {
        println(a[i]);
    }

    return 0;
}
