#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int countAdjacentRooms(const vector<string>& grid, int x, int y) {
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    int adjacent = 0;
    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (0 <= nx && nx < (int)grid.size() && 0 <= ny && ny < (int)grid[0].size() &&
            grid[nx][ny] == '.') {
            ++adjacent;
        }
    }
    return adjacent;
}

vector<pair<int, int>> buildTreeGrid(int r, int c, int targetRooms, int mode) {
    vector<string> grid(r, string(c, '#'));
    vector<pair<int, int>> rooms;

    auto addRoom = [&](int x, int y) {
        if (grid[x][y] == '.') {
            return;
        }
        grid[x][y] = '.';
        rooms.push_back({x, y});
    };

    if (mode == 0) {
        int row = rnd.next(r);
        int start = rnd.next(0, c - targetRooms);
        for (int j = 0; j < targetRooms; ++j) {
            addRoom(row, start + j);
        }
        return rooms;
    }

    if (mode == 1) {
        int col = rnd.next(c);
        int start = rnd.next(0, r - targetRooms);
        for (int i = 0; i < targetRooms; ++i) {
            addRoom(start + i, col);
        }
        return rooms;
    }

    addRoom(rnd.next(r), rnd.next(c));
    while ((int)rooms.size() < targetRooms) {
        vector<pair<int, int>> candidates;
        for (int x = 0; x < r; ++x) {
            for (int y = 0; y < c; ++y) {
                if (grid[x][y] == '#' && countAdjacentRooms(grid, x, y) == 1) {
                    candidates.push_back({x, y});
                }
            }
        }
        if (candidates.empty()) {
            break;
        }
        pair<int, int> nextRoom = candidates[rnd.next((int)candidates.size())];
        addRoom(nextRoom.first, nextRoom.second);
    }
    return rooms;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int r = rnd.next(1, 8);
    int c = rnd.next(1, 8);
    int maxRooms = min(r * c, 18);
    int targetRooms = rnd.next(1, maxRooms);
    if (mode == 0) {
        c = max(c, targetRooms);
    } else if (mode == 1) {
        r = max(r, targetRooms);
    }

    vector<pair<int, int>> rooms = buildTreeGrid(r, c, targetRooms, mode);
    vector<string> grid(r, string(c, '#'));
    for (auto [x, y] : rooms) {
        grid[x][y] = '.';
    }

    int m = rnd.next(2, min(30, max(2, (int)rooms.size() * 3)));
    int costLimit = rnd.any(vector<int>{3, 10, 100, 1000000000});

    println(r, c, m);
    for (const string& row : grid) {
        println(row);
    }

    for (int matrix = 0; matrix < 3; ++matrix) {
        for (int i = 0; i < r; ++i) {
            vector<int> values;
            for (int j = 0; j < c; ++j) {
                values.push_back(grid[i][j] == '.' ? rnd.next(1, costLimit) : 0);
            }
            println(values);
        }
    }

    for (int i = 0; i < m; ++i) {
        pair<int, int> task;
        if (i > 0 && rnd.next(100) < 35) {
            task = rooms[rnd.next(min((int)rooms.size(), i)) % rooms.size()];
        } else {
            task = rooms[rnd.next((int)rooms.size())];
        }
        println(task.first, task.second);
    }

    return 0;
}
