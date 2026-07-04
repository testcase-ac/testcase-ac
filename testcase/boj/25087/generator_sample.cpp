#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 18);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int r = rnd.next(1, 12);
        int c = rnd.next(1, 12);
        vector<string> grid(r, string(c, '#'));

        if (mode == 0) {
            for (int i = 0; i < r; ++i)
                for (int j = 0; j < c; ++j)
                    grid[i][j] = '*';
        } else if (mode == 1) {
            for (int i = 0; i < r; ++i)
                for (int j = 0; j < c; ++j)
                    grid[i][j] = ((i % 2 == 1) && (j % 2 == 1)) ? '#' : '*';
        } else if (mode == 2) {
            int percentEmpty = rnd.next(20, 85);
            for (int i = 0; i < r; ++i)
                for (int j = 0; j < c; ++j)
                    grid[i][j] = rnd.next(1, 100) <= percentEmpty ? '*' : '#';
        } else if (mode == 3) {
            int target = rnd.next(1, r * c);
            vector<pair<int, int>> cells;
            grid[0][0] = '*';
            cells.push_back({0, 0});

            while ((int)cells.size() < target) {
                auto [x, y] = rnd.any(cells);
                vector<pair<int, int>> next;
                if (x > 0 && grid[x - 1][y] == '#') next.push_back({x - 1, y});
                if (x + 1 < r && grid[x + 1][y] == '#') next.push_back({x + 1, y});
                if (y > 0 && grid[x][y - 1] == '#') next.push_back({x, y - 1});
                if (y + 1 < c && grid[x][y + 1] == '#') next.push_back({x, y + 1});
                if (next.empty()) continue;

                auto chosen = rnd.any(next);
                grid[chosen.first][chosen.second] = '*';
                cells.push_back(chosen);
            }
        } else {
            for (int i = 0; i < r; ++i)
                for (int j = 0; j < c; ++j)
                    grid[i][j] = '#';

            grid[0][0] = '*';
            if (c > 1 && rnd.next(0, 1)) grid[0][1] = '*';
            if (r > 1 && rnd.next(0, 1)) grid[1][0] = '*';

            int islands = rnd.next(1, 4);
            for (int k = 0; k < islands; ++k) {
                int x = rnd.next(0, r - 1);
                int y = rnd.next(0, c - 1);
                grid[x][y] = '*';
                if (x + 1 < r && rnd.next(0, 1)) grid[x + 1][y] = '*';
                if (y + 1 < c && rnd.next(0, 1)) grid[x][y + 1] = '*';
            }
        }

        grid[0][0] = '*';

        println(r, c);
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
