#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int robot = 0;
    int box = 0;
    int target = 0;

    if (mode <= 1) {
        vector<int> positions;
        for (int i = 0; i < 10; ++i) positions.push_back(i);
        shuffle(positions.begin(), positions.end());
        robot = positions[0];
        box = positions[1];
        target = positions[2];
    } else if (mode == 2) {
        box = rnd.next(1, 8);
        robot = rnd.next(0, box - 1);
        target = rnd.next(box + 1, 9);
    } else if (mode == 3) {
        box = rnd.next(1, 8);
        target = rnd.next(0, box - 1);
        robot = rnd.next(box + 1, 9);
    } else if (mode == 4) {
        box = rnd.any(vector<int>{0, 9});
        if (box == 0) {
            robot = rnd.next(1, 8);
            target = rnd.next(robot + 1, 9);
        } else {
            robot = rnd.next(1, 8);
            target = rnd.next(0, robot - 1);
        }
    } else {
        box = rnd.next(1, 8);
        if (rnd.next(0, 1) == 0) {
            robot = box - 1;
            target = rnd.next(box + 1, 9);
        } else {
            robot = box + 1;
            target = rnd.next(0, box - 1);
        }
    }

    string cells(10, '.');
    cells[robot] = '@';
    cells[box] = '#';
    cells[target] = '!';
    println(cells);

    return 0;
}
