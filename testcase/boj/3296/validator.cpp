#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 50, "R");
    inf.readSpace();
    int c = inf.readInt(1, 50, "C");
    inf.readEoln();

    vector<string> grid(r);
    int starts = 0;
    int startRow = -1;
    int startCol = -1;
    for (int i = 0; i < r; ++i) {
        grid[i] = inf.readToken("[.X*]{1,50}", "map_row");
        inf.readEoln();
        ensuref((int)grid[i].size() == c,
                "map row %d has length %d, expected %d", i + 1,
                (int)grid[i].size(), c);
        for (int j = 0; j < c; ++j) {
            if (grid[i][j] == '*') {
                ++starts;
                startRow = i;
                startCol = j;
            }
        }
    }
    ensuref(starts == 1, "expected exactly one initial position, found %d", starts);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    vector<vector<char>> reachable(r, vector<char>(c, 0));
    reachable[startRow][startCol] = 1;

    string previous;
    for (int moveIndex = 0; moveIndex < n; ++moveIndex) {
        string direction = inf.readToken("NORTH|SOUTH|WEST|EAST", "direction");
        inf.readEoln();
        ensuref(moveIndex == 0 || direction != previous,
                "consecutive directions %d and %d are both %s", moveIndex,
                moveIndex + 1, direction.c_str());
        previous = direction;

        int dr = 0;
        int dc = 0;
        if (direction == "NORTH") {
            dr = -1;
        } else if (direction == "SOUTH") {
            dr = 1;
        } else if (direction == "WEST") {
            dc = -1;
        } else {
            dc = 1;
        }

        vector<vector<char>> next(r, vector<char>(c, 0));
        int count = 0;
        for (int row = 0; row < r; ++row) {
            for (int col = 0; col < c; ++col) {
                if (!reachable[row][col]) {
                    continue;
                }
                int nr = row + dr;
                int nc = col + dc;
                while (0 <= nr && nr < r && 0 <= nc && nc < c &&
                       grid[nr][nc] != 'X') {
                    if (!next[nr][nc]) {
                        next[nr][nc] = 1;
                        ++count;
                    }
                    nr += dr;
                    nc += dc;
                }
            }
        }
        ensuref(count > 0, "no possible position after direction %d", moveIndex + 1);
        reachable = next;
    }

    inf.readEof();
}
