#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(3, 50, "N");
    inf.readSpace();
    int M = inf.readInt(3, 50, "M");
    inf.readEoln();

    // 2. Read the map
    vector<string> grid(N);
    int star_count = 0;
    int star_r = -1, star_c = -1;
    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readLine("[A-Z\\-\\*]{"+to_string(M)+","+to_string(M)+"}", "map_row");
        ensuref((int)grid[i].size() == M, "Row %d: Expected length %d, got %d", i+1, M, (int)grid[i].size());
        for (int j = 0; j < M; ++j) {
            char ch = grid[i][j];
            if (ch == '*') {
                ++star_count;
                star_r = i;
                star_c = j;
            }
            ensuref(
                (ch == '-') || (ch == '*') || (ch >= 'A' && ch <= 'Z'),
                "Invalid character '%c' at row %d, col %d", ch, i+1, j+1
            );
        }
    }

    // 3. Check there is exactly one '*'
    ensuref(star_count == 1, "There must be exactly one '*' (capital), found %d", star_count);

    // 4. Check that '*' is not on border
    ensuref(
        star_r > 0 && star_r < N-1 && star_c > 0 && star_c < M-1,
        "The '*' must not be on the border (row=%d, col=%d, N=%d, M=%d)", star_r+1, star_c+1, N, M
    );

    // 5. Read the 26 integers for obstacle sizes
    vector<int> obs = inf.readInts(26, 1, 1000000, "obstacle_sizes");
    inf.readEoln();

    // 6. No further lines
    inf.readEof();
}
