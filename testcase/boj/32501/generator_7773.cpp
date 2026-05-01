#include "testlib.h"
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: orientation of foci
    int type = rnd.next(0, 2);
    int x1, y1, x2, y2;
    if (type == 0) {
        // Horizontal: same y
        int y = rnd.next(-100, 100);
        x1 = rnd.next(-100, 100);
        x2 = rnd.next(-100, 100);
        y1 = y2 = y;
    } else if (type == 1) {
        // Vertical: same x
        int x = rnd.next(-100, 100);
        y1 = rnd.next(-100, 100);
        y2 = rnd.next(-100, 100);
        x1 = x2 = x;
    } else {
        // Random distinct foci
        do {
            x1 = rnd.next(-100, 100);
            y1 = rnd.next(-100, 100);
            x2 = rnd.next(-100, 100);
            y2 = rnd.next(-100, 100);
        } while (x1 == x2 && y1 == y2);
    }

    // Compute minimum major axis length (distance between foci)
    long long dx = x2 - x1;
    long long dy = y2 - y1;
    double dist = sqrt(double(dx * dx + dy * dy));
    int minA = int(ceil(dist - 1e-9));
    if (minA < 0) minA = 0;

    // Allow offset to create larger ellipses
    int offset = rnd.next(0, 500);
    int maxA = min(minA + offset, 1000);
    int a = rnd.next(minA, maxA);

    // Output one test case
    println(x1, y1, x2, y2, a);

    return 0;
}
