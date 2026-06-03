#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int n = 15;
    const string cats = "wbg";
    const string backgrounds = "royp";

    char cat = cats[rnd.next((int)cats.size())];
    vector<vector<char>> grid(n, vector<char>(n, backgrounds[0]));

    int backgroundMode = rnd.next(4);
    char dominantBackground = backgrounds[rnd.next((int)backgrounds.size())];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (backgroundMode == 0) {
                grid[i][j] = dominantBackground;
            } else if (backgroundMode == 1) {
                grid[i][j] = backgrounds[(i + j + rnd.next(2)) % (int)backgrounds.size()];
            } else if (backgroundMode == 2) {
                grid[i][j] = rnd.next(100) < 75 ? dominantBackground : backgrounds[rnd.next((int)backgrounds.size())];
            } else {
                grid[i][j] = backgrounds[rnd.next((int)backgrounds.size())];
            }
        }
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    int catMode = rnd.next(5);
    if (catMode == 0) {
        grid[cells[0].first][cells[0].second] = cat;
    } else if (catMode == 1) {
        int count = rnd.next(2, 12);
        for (int k = 0; k < count; ++k) {
            grid[cells[k].first][cells[k].second] = cat;
        }
    } else if (catMode == 2) {
        int row = rnd.next(n);
        int from = rnd.next(0, n - 1);
        int to = rnd.next(from, n - 1);
        for (int j = from; j <= to; ++j) {
            grid[row][j] = cat;
        }
    } else if (catMode == 3) {
        int col = rnd.next(n);
        int from = rnd.next(0, n - 1);
        int to = rnd.next(from, n - 1);
        for (int i = from; i <= to; ++i) {
            grid[i][col] = cat;
        }
    } else {
        int top = rnd.next(0, n - 1);
        int left = rnd.next(0, n - 1);
        int height = rnd.next(1, min(5, n - top));
        int width = rnd.next(1, min(5, n - left));
        for (int i = top; i < top + height; ++i) {
            for (int j = left; j < left + width; ++j) {
                if (rnd.next(100) < 70) {
                    grid[i][j] = cat;
                }
            }
        }
        grid[top][left] = cat;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) {
                cout << ' ';
            }
            cout << grid[i][j];
        }
        cout << '\n';
    }

    return 0;
}
