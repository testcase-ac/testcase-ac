#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

char toward(int r1, int c1, int r2, int c2) {
    if (r2 == r1 - 1) return 'U';
    if (r2 == r1 + 1) return 'D';
    if (c2 == c1 - 1) return 'L';
    return 'R';
}

void makeAllEscape(vector<string>& maze) {
    int n = maze.size();
    int m = maze[0].size();
    int side = rnd.next(4);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (side == 0) maze[r][c] = 'U';
            if (side == 1) maze[r][c] = 'D';
            if (side == 2) maze[r][c] = 'L';
            if (side == 3) maze[r][c] = 'R';
        }
    }
}

void makeInnerCycle(vector<string>& maze) {
    int n = maze.size();
    int m = maze[0].size();
    makeAllEscape(maze);

    int top = rnd.next(0, n - 2);
    int left = rnd.next(0, m - 2);
    int height = rnd.next(2, n - top);
    int width = rnd.next(2, m - left);
    int bottom = top + height - 1;
    int right = left + width - 1;

    for (int c = left; c < right; ++c) maze[top][c] = 'R';
    for (int r = top; r < bottom; ++r) maze[r][right] = 'D';
    for (int c = right; c > left; --c) maze[bottom][c] = 'L';
    for (int r = bottom; r > top; --r) maze[r][left] = 'U';

    for (int r = top + 1; r < bottom; ++r) {
        for (int c = left + 1; c < right; ++c) {
            int edge = rnd.next(4);
            if (edge == 0) maze[r][c] = 'U';
            if (edge == 1) maze[r][c] = 'D';
            if (edge == 2) maze[r][c] = 'L';
            if (edge == 3) maze[r][c] = 'R';
        }
    }
}

void makeSnake(vector<string>& maze, bool exits) {
    int n = maze.size();
    int m = maze[0].size();
    vector<pair<int, int>> cells;
    for (int r = 0; r < n; ++r) {
        if (r % 2 == 0) {
            for (int c = 0; c < m; ++c) cells.push_back({r, c});
        } else {
            for (int c = m - 1; c >= 0; --c) cells.push_back({r, c});
        }
    }

    for (int i = 0; i + 1 < int(cells.size()); ++i) {
        auto [r1, c1] = cells[i];
        auto [r2, c2] = cells[i + 1];
        maze[r1][c1] = toward(r1, c1, r2, c2);
    }

    auto [lr, lc] = cells.back();
    if (exits) {
        maze[lr][lc] = (lr == n - 1 ? 'D' : 'U');
    } else {
        auto [pr, pc] = cells[cells.size() - 2];
        maze[lr][lc] = toward(lr, lc, pr, pc);
    }
}

void makeRandomLocal(vector<string>& maze) {
    int n = maze.size();
    int m = maze[0].size();
    const string dirs = "URDL";
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            string choices;
            if (r > 0) choices += 'U';
            else if (rnd.next(100) < 35) choices += 'U';
            if (r + 1 < n) choices += 'D';
            else if (rnd.next(100) < 35) choices += 'D';
            if (c > 0) choices += 'L';
            else if (rnd.next(100) < 35) choices += 'L';
            if (c + 1 < m) choices += 'R';
            else if (rnd.next(100) < 35) choices += 'R';
            if (choices.empty()) choices = dirs;
            maze[r][c] = rnd.any(choices);
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 14);
    int m = rnd.next(3, 14);
    if (rnd.next(10) == 0) {
        n = rnd.next(15, 30);
        m = rnd.next(15, 30);
    }

    vector<string> maze(n, string(m, 'U'));
    int mode = rnd.next(5);
    if (mode == 0) makeRandomLocal(maze);
    if (mode == 1) makeAllEscape(maze);
    if (mode == 2) makeInnerCycle(maze);
    if (mode == 3) makeSnake(maze, true);
    if (mode == 4) makeSnake(maze, false);

    println(n, m);
    for (const string& row : maze) println(row);
    return 0;
}
