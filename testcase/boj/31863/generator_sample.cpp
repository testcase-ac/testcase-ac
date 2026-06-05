#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char weightedCell(int mode) {
    int roll = rnd.next(100);
    if (mode == 0) {
        if (roll < 55) return '.';
        if (roll < 75) return '*';
        if (roll < 90) return '#';
        return '|';
    }
    if (mode == 1) {
        if (roll < 35) return '|';
        if (roll < 58) return '*';
        if (roll < 78) return '#';
        return '.';
    }
    if (mode == 2) {
        if (roll < 38) return '*';
        if (roll < 73) return '#';
        if (roll < 88) return '.';
        return '|';
    }
    if (roll < 70) return '.';
    if (roll < 85) return '*';
    if (roll < 95) return '#';
    return '|';
}

bool inside(int r, int c, int n, int m) {
    return 0 <= r && r < n && 0 <= c && c < m;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n, m;
    if (mode == 4) {
        if (rnd.next(2) == 0) {
            n = rnd.next(2, 3);
            m = rnd.next(2, 18);
        } else {
            n = rnd.next(2, 18);
            m = rnd.next(2, 3);
        }
    } else {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
    }

    vector<string> grid(n, string(m, '.'));
    int er = rnd.next(n);
    int ec = rnd.next(m);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            grid[r][c] = weightedCell(mode);
        }
    }

    if (mode == 3) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                grid[r][c] = rnd.next(3) == 0 ? '#' : '.';
            }
        }
        for (int d = 1; d <= 2; ++d) {
            if (inside(er + d, ec, n, m)) grid[er + d][ec] = rnd.next(2) ? '*' : '#';
            if (inside(er - d, ec, n, m)) grid[er - d][ec] = rnd.next(2) ? '*' : '#';
            if (inside(er, ec + d, n, m)) grid[er][ec + d] = rnd.next(2) ? '*' : '#';
            if (inside(er, ec - d, n, m)) grid[er][ec - d] = rnd.next(2) ? '*' : '#';
        }
        int barriers = rnd.next(0, 4);
        for (int i = 0; i < barriers; ++i) {
            int dir = rnd.next(4);
            int dist = rnd.next(1, 2);
            int rr = er + (dir == 0) * dist - (dir == 1) * dist;
            int cc = ec + (dir == 2) * dist - (dir == 3) * dist;
            if (inside(rr, cc, n, m)) grid[rr][cc] = '|';
        }
    }

    if (mode == 4) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                int v = (r + c + rnd.next(3)) % 5;
                grid[r][c] = v == 0 ? '|' : (v <= 2 ? '*' : '#');
            }
        }
    }

    grid[er][ec] = '@';

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }
    return 0;
}
