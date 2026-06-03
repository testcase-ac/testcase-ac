#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<int>> grid(9, vector<int>(9));
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int value = rnd.next(0, 99);
        for (int r = 0; r < 9; ++r)
            for (int c = 0; c < 9; ++c)
                grid[r][c] = value;
    } else if (mode == 1) {
        int maxValue = rnd.next(1, 99);
        for (int r = 0; r < 9; ++r)
            for (int c = 0; c < 9; ++c)
                grid[r][c] = rnd.next(0, maxValue - 1);

        int r = rnd.next(0, 8);
        int c = rnd.next(0, 8);
        grid[r][c] = maxValue;
    } else if (mode == 2) {
        int maxValue = rnd.next(1, 99);
        for (int r = 0; r < 9; ++r)
            for (int c = 0; c < 9; ++c)
                grid[r][c] = rnd.next(0, maxValue - 1);

        int count = rnd.next(2, 12);
        for (int i = 0; i < count; ++i)
            grid[rnd.next(0, 8)][rnd.next(0, 8)] = maxValue;
    } else if (mode == 3) {
        int maxValue = rnd.next(50, 99);
        for (int r = 0; r < 9; ++r)
            for (int c = 0; c < 9; ++c)
                grid[r][c] = rnd.next(0, maxValue - 1);

        vector<pair<int, int>> cells = {{0, 0}, {0, 8}, {8, 0}, {8, 8}};
        auto cell = rnd.any(cells);
        grid[cell.first][cell.second] = maxValue;
    } else if (mode == 4) {
        int maxValue = rnd.next(1, 99);
        for (int r = 0; r < 9; ++r)
            for (int c = 0; c < 9; ++c)
                grid[r][c] = rnd.next(0, maxValue - 1);

        int edge = rnd.next(0, 3);
        int offset = rnd.next(0, 8);
        int r = edge == 0 ? 0 : edge == 1 ? 8 : offset;
        int c = edge == 2 ? 0 : edge == 3 ? 8 : offset;
        grid[r][c] = maxValue;
    } else {
        int low = rnd.next(0, 70);
        int high = rnd.next(low, 99);
        for (int r = 0; r < 9; ++r)
            for (int c = 0; c < 9; ++c)
                grid[r][c] = rnd.next(low, high);
    }

    for (int r = 0; r < 9; ++r)
        println(grid[r]);

    return 0;
}
