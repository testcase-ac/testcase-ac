#include "testlib.h"
#include <vector>
#include <string>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(1, 10, "R");
    inf.readSpace();
    int C = inf.readInt(1, 10, "C");
    inf.readEoln();

    // Read the map
    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
        // readLine consumes the end of line
        string row = inf.readLine("[.X]+", "row");
        ensuref((int)row.size() == C,
                "Length of row %d is %d but expected %d", i, (int)row.size(), C);
        // regex already ensures only '.' or 'X'
        grid[i] = row;
    }

    // Simulate 50-year submerging
    vector<string> after(R, string(C, '.'));
    int remaining = 0;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == 'X') {
                int water = 0;
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    // outside or '.' is water
                    if (ni < 0 || ni >= R || nj < 0 || nj >= C || grid[ni][nj] == '.')
                        water++;
                }
                if (water < 3) {
                    after[i][j] = 'X';
                    remaining++;
                }
            }
        }
    }

    // According to the problem, at least one land remains after 50 years
    ensuref(remaining >= 1,
            "All land will be submerged after 50 years (remaining = %d)", remaining);

    inf.readEof();
    return 0;
}
