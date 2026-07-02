#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int r = rnd.next(1, 10);
    int c = rnd.next(2, 12);
    if (rnd.next(5) == 0) {
        r = rnd.next(2, 12);
        c = rnd.next(1, 10);
    }

    vector<string> grid(r, string(c, '.'));
    vector<pair<int, int>> cells;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    int mode = rnd.next(0, 4);
    pair<int, int> first = cells[0];
    pair<int, int> second = cells[1];

    if (mode == 0) {
        // Adjacent A cells exercise the one-instruction boundary.
        vector<pair<pair<int, int>, pair<int, int>>> adjacent;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (i + 1 < r) adjacent.push_back({{i, j}, {i + 1, j}});
                if (j + 1 < c) adjacent.push_back({{i, j}, {i, j + 1}});
            }
        }
        auto choice = rnd.any(adjacent);
        first = choice.first;
        second = choice.second;
    } else if (mode == 1 && r >= 2 && c >= 2) {
        // A wall with one random opening creates narrow-path cases.
        if (rnd.next(2) == 0) {
            int wall = rnd.next(0, r - 1);
            int gap = rnd.next(0, c - 1);
            for (int j = 0; j < c; ++j) grid[wall][j] = '#';
            grid[wall][gap] = '.';
            first = {rnd.next(0, wall), rnd.next(0, c - 1)};
            second = {rnd.next(wall, r - 1), rnd.next(0, c - 1)};
            if (first == second) second = {wall, gap};
        } else {
            int wall = rnd.next(0, c - 1);
            int gap = rnd.next(0, r - 1);
            for (int i = 0; i < r; ++i) grid[i][wall] = '#';
            grid[gap][wall] = '.';
            first = {rnd.next(0, r - 1), rnd.next(0, wall)};
            second = {rnd.next(0, r - 1), rnd.next(wall, c - 1)};
            if (first == second) second = {gap, wall};
        }
    } else if (mode == 2 && r >= 2 && c >= 2) {
        // Fully separated regions should often force an impossible answer.
        if (rnd.next(2) == 0) {
            int wall = rnd.next(0, r - 1);
            for (int j = 0; j < c; ++j) grid[wall][j] = '#';
            first = {0, rnd.next(0, c - 1)};
            second = {r - 1, rnd.next(0, c - 1)};
        } else {
            int wall = rnd.next(0, c - 1);
            for (int i = 0; i < r; ++i) grid[i][wall] = '#';
            first = {rnd.next(0, r - 1), 0};
            second = {rnd.next(0, r - 1), c - 1};
        }
        if (first == second) second = cells[1];
    }

    if (first == second) {
        for (const auto& cell : cells) {
            if (cell != first) {
                second = cell;
                break;
            }
        }
    }

    grid[first.first][first.second] = 'A';
    grid[second.first][second.second] = 'A';

    int obstacleChance = rnd.next(0, 35);
    int atomChance = rnd.next(0, 70);
    if (mode == 3) atomChance = rnd.next(45, 90);
    if (mode == 4) obstacleChance = rnd.next(30, 60);

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (grid[i][j] == 'A' || grid[i][j] == '#') continue;
            int roll = rnd.next(0, 99);
            if (roll < obstacleChance) {
                grid[i][j] = '#';
            } else if (roll < obstacleChance + atomChance) {
                grid[i][j] = 'O';
            }
        }
    }

    println(r, c);
    for (const string& row : grid) {
        println(row);
    }
    return 0;
}
