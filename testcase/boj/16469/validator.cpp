#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(2, 100, "R");
    inf.readSpace();
    int C = inf.readInt(2, 100, "C");
    inf.readEoln();

    // Read maze
    vector<vector<int>> maze(R, vector<int>(C));
    for (int i = 0; i < R; ++i) {
        string line = inf.readLine("[01]{"+to_string(C)+","+to_string(C)+"}", "maze_row");
        ensuref((int)line.size() == C, "Maze row %d has length %d, expected %d", i+1, (int)line.size(), C);
        for (int j = 0; j < C; ++j) {
            ensuref(line[j] == '0' || line[j] == '1', "Maze row %d col %d: invalid character '%c'", i+1, j+1, line[j]);
            maze[i][j] = line[j] - '0';
        }
    }

    // Read 3 starting positions
    set<pair<int,int>> used_positions;
    vector<pair<int,int>> starts;
    for (int k = 0; k < 3; ++k) {
        int x = inf.readInt(1, R, "X_"+to_string(k+1));
        inf.readSpace();
        int y = inf.readInt(1, C, "Y_"+to_string(k+1));
        inf.readEoln();

        ensuref(maze[x-1][y-1] == 0, "Starting position %d (%d, %d) is not on a walkable cell", k+1, x, y);
        ensuref(!used_positions.count({x-1, y-1}), "Starting positions overlap at (%d, %d)", x, y);
        used_positions.insert({x-1, y-1});
        starts.push_back({x-1, y-1});
    }

    // No extra input
    inf.readEof();
}
