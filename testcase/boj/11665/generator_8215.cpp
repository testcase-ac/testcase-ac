#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of boxes
    int N = rnd.next(1, 7);

    // Sample a common intersection region [Xl0, Xh0], [Yl0, Yh0], [Zl0, Zh0]
    int Xl0 = rnd.next(1, 600);
    int Xh0 = rnd.next(Xl0 + 1, min(1000, Xl0 + 200));
    int Yl0 = rnd.next(1, 600);
    int Yh0 = rnd.next(Yl0 + 1, min(1000, Yl0 + 200));
    int Zl0 = rnd.next(1, 600);
    int Zh0 = rnd.next(Zl0 + 1, min(1000, Zl0 + 200));

    // Determine if we can force an empty intersection
    vector<int> disAxes;
    if (Xl0 > 1 || Xh0 < 1000) disAxes.push_back(0);
    if (Yl0 > 1 || Yh0 < 1000) disAxes.push_back(1);
    if (Zl0 > 1 || Zh0 < 1000) disAxes.push_back(2);
    bool makeEmpty = (N > 1 && !disAxes.empty() && rnd.next(0, 1) == 0);

    vector<array<int,6>> boxes;
    int normalCount = makeEmpty ? N - 1 : N;
    // Generate boxes that all contain the common region
    for (int i = 0; i < normalCount; i++) {
        int padLX = rnd.next(0, Xl0 - 1), padRX = rnd.next(0, 1000 - Xh0);
        int x1 = Xl0 - padLX, x2 = Xh0 + padRX;
        int padLY = rnd.next(0, Yl0 - 1), padRY = rnd.next(0, 1000 - Yh0);
        int y1 = Yl0 - padLY, y2 = Yh0 + padRY;
        int padLZ = rnd.next(0, Zl0 - 1), padRZ = rnd.next(0, 1000 - Zh0);
        int z1 = Zl0 - padLZ, z2 = Zh0 + padRZ;
        boxes.push_back({x1, y1, z1, x2, y2, z2});
    }

    // If forcing empty intersection, add one disjoint box along a random feasible axis
    if (makeEmpty) {
        int axis = rnd.any(disAxes);
        int x1, y1, z1, x2, y2, z2;
        if (axis == 0) {
            // Disjoint in X
            bool canLeft = Xl0 > 1, canRight = Xh0 < 1000;
            bool left = canLeft && (!canRight || rnd.next(0,1) == 0);
            if (left) {
                x2 = rnd.next(1, Xl0);
                x1 = rnd.next(1, x2 - 1);
            } else {
                x1 = rnd.next(Xh0, 1000);
                x2 = rnd.next(x1 + 1, 1000);
            }
            // Cover Y,Z fully
            int padLY = rnd.next(0, Yl0 - 1), padRY = rnd.next(0, 1000 - Yh0);
            y1 = Yl0 - padLY; y2 = Yh0 + padRY;
            int padLZ = rnd.next(0, Zl0 - 1), padRZ = rnd.next(0, 1000 - Zh0);
            z1 = Zl0 - padLZ; z2 = Zh0 + padRZ;
        } else if (axis == 1) {
            // Disjoint in Y
            bool canLeft = Yl0 > 1, canRight = Yh0 < 1000;
            bool left = canLeft && (!canRight || rnd.next(0,1) == 0);
            if (left) {
                y2 = rnd.next(1, Yl0);
                y1 = rnd.next(1, y2 - 1);
            } else {
                y1 = rnd.next(Yh0, 1000);
                y2 = rnd.next(y1 + 1, 1000);
            }
            int padLX = rnd.next(0, Xl0 - 1), padRX = rnd.next(0, 1000 - Xh0);
            x1 = Xl0 - padLX; x2 = Xh0 + padRX;
            int padLZ = rnd.next(0, Zl0 - 1), padRZ = rnd.next(0, 1000 - Zh0);
            z1 = Zl0 - padLZ; z2 = Zh0 + padRZ;
        } else {
            // Disjoint in Z
            bool canLeft = Zl0 > 1, canRight = Zh0 < 1000;
            bool left = canLeft && (!canRight || rnd.next(0,1) == 0);
            if (left) {
                z2 = rnd.next(1, Zl0);
                z1 = rnd.next(1, z2 - 1);
            } else {
                z1 = rnd.next(Zh0, 1000);
                z2 = rnd.next(z1 + 1, 1000);
            }
            int padLX = rnd.next(0, Xl0 - 1), padRX = rnd.next(0, 1000 - Xh0);
            x1 = Xl0 - padLX; x2 = Xh0 + padRX;
            int padLY = rnd.next(0, Yl0 - 1), padRY = rnd.next(0, 1000 - Yh0);
            y1 = Yl0 - padLY; y2 = Yh0 + padRY;
        }
        boxes.push_back({x1, y1, z1, x2, y2, z2});
    }

    // Output
    println(N);
    for (auto &b : boxes)
        println(b[0], b[1], b[2], b[3], b[4], b[5]);
    return 0;
}
