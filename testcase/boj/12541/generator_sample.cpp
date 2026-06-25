#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(1, 10);
    println(testCases);

    for (int tc = 0; tc < testCases; ++tc) {
        int mode = rnd.next(6);
        int length;
        int width;

        if (mode == 0) {
            length = rnd.next(1, 3);
            width = rnd.next(1, 3);
        } else if (mode == 1) {
            length = rnd.next(1, 8);
            width = rnd.next(1, 2);
        } else if (mode == 2) {
            length = rnd.next(1, 2);
            width = rnd.next(1, 8);
        } else if (mode == 3) {
            length = rnd.next(4, 12);
            width = rnd.next(4, 12);
        } else if (mode == 4) {
            length = rnd.next(8, 18);
            width = rnd.next(2, 8);
        } else {
            length = rnd.next(2, 8);
            width = rnd.next(8, 18);
        }

        vector<string> grid(width, string(length, 'G'));

        int shrubMode = rnd.next(4);
        for (int r = 0; r < width; ++r) {
            for (int c = 0; c < length; ++c) {
                bool shrub = false;
                if (shrubMode == 0) {
                    shrub = rnd.next(4) == 0;
                } else if (shrubMode == 1) {
                    shrub = (r + c) % 2 == rnd.next(2);
                } else if (shrubMode == 2) {
                    shrub = r == c || r + c == length - 1;
                } else {
                    shrub = rnd.next(10) < 7;
                }
                if (shrub) {
                    grid[r][c] = 'S';
                }
            }
        }

        int cells = length * width;
        int obstacleCount = rnd.next(0, min(4, cells));
        vector<int> positions;
        for (int i = 0; i < cells; ++i) {
            positions.push_back(i);
        }
        shuffle(positions.begin(), positions.end());

        const string obstacles = "RWT";
        for (int i = 0; i < obstacleCount; ++i) {
            int pos = positions[i];
            int r = pos / length;
            int c = pos % length;
            grid[r][c] = obstacles[rnd.next(static_cast<int>(obstacles.size()))];
        }

        println(length, width);
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
