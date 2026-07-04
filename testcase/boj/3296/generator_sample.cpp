#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

struct Direction {
    string name;
    int dr;
    int dc;
};

vector<vector<char>> stepReachable(const vector<string>& grid,
                                   const vector<vector<char>>& reachable,
                                   const Direction& direction) {
    int r = (int)grid.size();
    int c = (int)grid[0].size();
    vector<vector<char>> next(r, vector<char>(c, 0));

    for (int row = 0; row < r; ++row) {
        for (int col = 0; col < c; ++col) {
            if (!reachable[row][col]) {
                continue;
            }

            int nr = row + direction.dr;
            int nc = col + direction.dc;
            while (0 <= nr && nr < r && 0 <= nc && nc < c && grid[nr][nc] != 'X') {
                next[nr][nc] = 1;
                nr += direction.dr;
                nc += direction.dc;
            }
        }
    }

    return next;
}

bool hasReachable(const vector<vector<char>>& reachable) {
    for (const auto& row : reachable) {
        for (char cell : row) {
            if (cell) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<Direction> directions = {
        {"NORTH", -1, 0},
        {"SOUTH", 1, 0},
        {"WEST", 0, -1},
        {"EAST", 0, 1},
    };

    int r = rnd.next(2, 12);
    int c = rnd.next(2, 12);
    int mode = rnd.next(4);

    vector<string> grid(r, string(c, '.'));
    for (int row = 0; row < r; ++row) {
        for (int col = 0; col < c; ++col) {
            int obstaclePercent = 0;
            if (mode == 1) {
                obstaclePercent = 15;
            } else if (mode == 2) {
                obstaclePercent = 30;
            } else if (mode == 3) {
                obstaclePercent = (row % 2 == 1 && col + 1 < c) ? 45 : 5;
            }

            if (rnd.next(100) < obstaclePercent) {
                grid[row][col] = 'X';
            }
        }
    }

    vector<pair<int, int>> open;
    for (int row = 0; row < r; ++row) {
        for (int col = 0; col < c; ++col) {
            if (grid[row][col] == '.') {
                open.push_back({row, col});
            }
        }
    }

    if (open.empty()) {
        pair<int, int> reopened = {rnd.next(r), rnd.next(c)};
        grid[reopened.first][reopened.second] = '.';
        open.push_back(reopened);
    }

    pair<int, int> start = rnd.any(open);
    grid[start.first][start.second] = '*';

    vector<vector<char>> reachable(r, vector<char>(c, 0));
    reachable[start.first][start.second] = 1;

    int targetMoves = rnd.next(1, 30);
    string previous;
    vector<string> moves;

    for (int moveIndex = 0; moveIndex < targetMoves; ++moveIndex) {
        vector<int> candidates;
        for (int i = 0; i < (int)directions.size(); ++i) {
            if (directions[i].name == previous) {
                continue;
            }
            if (hasReachable(stepReachable(grid, reachable, directions[i]))) {
                candidates.push_back(i);
            }
        }

        if (candidates.empty()) {
            break;
        }

        int chosen = rnd.any(candidates);
        reachable = stepReachable(grid, reachable, directions[chosen]);
        previous = directions[chosen].name;
        moves.push_back(previous);
    }

    if (moves.empty()) {
        grid.assign(2, string(2, '.'));
        r = 2;
        c = 2;
        grid[0][0] = '*';
        moves.push_back("EAST");
    }

    println(r, c);
    for (const string& row : grid) {
        println(row);
    }
    println((int)moves.size());
    for (const string& move : moves) {
        println(move);
    }

    return 0;
}
