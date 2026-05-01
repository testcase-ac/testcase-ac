#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose scenario: 0 = equal lengths, 1 = X < Y, 2 = X > Y
    int scenario = rnd.next(0, 2);
    int X, Y;

    if (scenario == 0) {
        // Equal-case: both from 1 to 9
        X = rnd.next(1, 9);
        Y = X;
    } else if (scenario == 1) {
        // X < Y: X from 1 to 8, Y from X+1 to 9
        X = rnd.next(1, 8);
        Y = rnd.next(X + 1, 9);
    } else {
        // X > Y: Y from 1 to 8, X from Y+1 to 9
        Y = rnd.next(1, 8);
        X = rnd.next(Y + 1, 9);
    }

    // Output X and Y
    println(X, Y);
    return 0;
}
