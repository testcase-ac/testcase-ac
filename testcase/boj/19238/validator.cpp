#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M, fuel
    int N = inf.readInt(2, 20, "N");
    inf.readSpace();
    int M = inf.readInt(1, N * N, "M");
    inf.readSpace();
    int fuel = inf.readInt(1, 500000, "fuel");
    inf.readEoln();

    // Grid input
    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = inf.readInt(0, 1, "grid");
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    // Taxi starting position
    int taxi_r = inf.readInt(1, N, "taxi_r");
    inf.readSpace();
    int taxi_c = inf.readInt(1, N, "taxi_c");
    inf.readEoln();
    ensuref(grid[taxi_r-1][taxi_c-1] == 0,
            "Taxi start position (%d,%d) is not on an empty cell", taxi_r, taxi_c);

    // Passengers
    set<pair<int,int>> starts;
    for (int i = 0; i < M; i++) {
        int sr = inf.readInt(1, N, "sr");
        inf.readSpace();
        int sc = inf.readInt(1, N, "sc");
        inf.readSpace();
        int dr = inf.readInt(1, N, "dr");
        inf.readSpace();
        int dc = inf.readInt(1, N, "dc");
        inf.readEoln();

        // Check emptiness
        ensuref(grid[sr-1][sc-1] == 0,
                "Passenger %d start (%d,%d) is not on an empty cell", i, sr, sc);
        ensuref(grid[dr-1][dc-1] == 0,
                "Passenger %d destination (%d,%d) is not on an empty cell", i, dr, dc);

        // Start != destination
        ensuref(!(sr == dr && sc == dc),
                "Passenger %d has identical start and destination (%d,%d)", i, sr, sc);

        // Unique start positions
        pair<int,int> p = {sr, sc};
        ensuref(!starts.count(p),
                "Duplicate passenger start at index %d: (%d,%d)", i, sr, sc);
        starts.insert(p);
    }

    inf.readEof();
    return 0;
}
