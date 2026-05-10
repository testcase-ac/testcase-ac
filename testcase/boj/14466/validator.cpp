#include "testlib.h"
#include <set>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid size N, number of cows K, number of roads R
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100, "K");
    inf.readSpace();
    // Maximum possible roads in an N x N grid is 2*N*(N-1)
    int maxR = 2 * N * (N - 1);
    int R = inf.readInt(0, maxR, "R");
    inf.readEoln();

    // K cannot exceed total cells
    ensuref(K <= N * N,
            "Number of cows K = %d exceeds total cells N*N = %d",
            K, N * N);

    // Validate roads
    set<pair<int,int>> roads;
    for (int i = 0; i < R; i++) {
        int r1 = inf.readInt(1, N, "road_r1");
        inf.readSpace();
        int c1 = inf.readInt(1, N, "road_c1");
        inf.readSpace();
        int r2 = inf.readInt(1, N, "road_r2");
        inf.readSpace();
        int c2 = inf.readInt(1, N, "road_c2");
        inf.readEoln();

        // Must be adjacent
        int dist = abs(r1 - r2) + abs(c1 - c2);
        ensuref(dist == 1,
                "Road %d at (%d,%d)-(%d,%d) is not between adjacent cells",
                i, r1, c1, r2, c2);

        // Encode cells to a unique id
        int id1 = (r1 - 1) * N + (c1 - 1);
        int id2 = (r2 - 1) * N + (c2 - 1);
        int a = min(id1, id2);
        int b = max(id1, id2);
        pair<int,int> e = make_pair(a, b);

        ensuref(!roads.count(e),
                "Duplicate road detected at index %d: (%d,%d)-(%d,%d)",
                i, r1, c1, r2, c2);
        roads.insert(e);
    }

    // Validate cow positions
    set<int> occupied;
    for (int i = 0; i < K; i++) {
        int r = inf.readInt(1, N, "cow_r");
        inf.readSpace();
        int c = inf.readInt(1, N, "cow_c");
        inf.readEoln();

        int id = (r - 1) * N + (c - 1);
        ensuref(!occupied.count(id),
                "Two cows placed at the same cell (%d,%d)", r, c);
        occupied.insert(id);
    }

    inf.readEof();
    return 0;
}
