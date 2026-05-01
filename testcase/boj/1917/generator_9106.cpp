#include "testlib.h"
using namespace std;

vector<pair<int,int>> rotateAndMirror(const vector<pair<int,int>>& cells) {
    vector<pair<int,int>> res = cells;

    int rot = rnd.next(0, 3); // 0,1,2,3 * 90 degrees
    for (auto &p : res) {
        int x = p.first, y = p.second;
        for (int i = 0; i < rot; ++i) {
            int nx = y;
            int ny = -x;
            x = nx;
            y = ny;
        }
        p.first = x;
        p.second = y;
    }

    int doMirror = rnd.next(0, 1);
    if (doMirror) {
        int horiz = rnd.next(0, 1);
        for (auto &p : res) {
            if (horiz) {
                p.first = -p.first;
            } else {
                p.second = -p.second;
            }
        }
    }

    return res;
}

vector<vector<int>> placeOnBoard(const vector<pair<int,int>>& cells) {
    const int SZ = 6;
    vector<vector<int>> board(SZ, vector<int>(SZ, 0));

    int minX = (int)1e9, maxX = (int)-1e9;
    int minY = (int)1e9, maxY = (int)-1e9;
    for (auto &p : cells) {
        minX = min(minX, p.first);
        maxX = max(maxX, p.first);
        minY = min(minY, p.second);
        maxY = max(maxY, p.second);
    }
    int w = maxX - minX + 1;
    int h = maxY - minY + 1;

    int offX = rnd.next(0, SZ - w);
    int offY = rnd.next(0, SZ - h);

    for (auto &p : cells) {
        int col = (p.first - minX) + offX;
        int row = (p.second - minY) + offY;
        board[row][col] = 1;
    }

    return board;
}

vector<vector<int>> generateKnownNetBoard() {
    // A standard valid cube net:
    //   (0,-2)
    //   (0,-1)
    // (-1,0) (0,0) (1,0)
    //   (0,1)
    vector<pair<int,int>> base = {
        {0, 0},
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},
        {0, -2}
    };

    auto cells = rotateAndMirror(base);
    return placeOnBoard(cells);
}

vector<vector<int>> generateRandomPolyominoBoard() {
    const int TARGET = 6;
    vector<pair<int,int>> cells;
    cells.push_back({0, 0});
    set<pair<int,int>> used;
    used.insert({0, 0});

    static const int dx[4] = {1, -1, 0, 0};
    static const int dy[4] = {0, 0, 1, -1};

    while ((int)cells.size() < TARGET) {
        set<pair<int,int>> frontier;
        for (auto &c : cells) {
            int x = c.first, y = c.second;
            for (int dir = 0; dir < 4; ++dir) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                pair<int,int> np = {nx, ny};
                if (!used.count(np)) {
                    frontier.insert(np);
                }
            }
        }
        vector<pair<int,int>> fr(frontier.begin(), frontier.end());
        pair<int,int> nextCell = rnd.any(fr);
        cells.push_back(nextCell);
        used.insert(nextCell);
    }

    cells = rotateAndMirror(cells);
    return placeOnBoard(cells);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<vector<int>>> boards;
    // Ensure at least one known valid net
    boards.push_back(generateKnownNetBoard());
    // Two more random polyominoes (likely mix of valid/invalid)
    boards.push_back(generateRandomPolyominoBoard());
    boards.push_back(generateRandomPolyominoBoard());

    for (int t = 0; t < 3; ++t) {
        for (int r = 0; r < 6; ++r) {
            println(boards[t][r]);
        }
    }

    return 0;
}
