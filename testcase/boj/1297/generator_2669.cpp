#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // TV aspect ratio H:W with small, hand-checkable numbers
    int H = rnd.next(1, 9);
    int W = rnd.next(H + 1, 10);  // ensure H < W

    // Diagonal length D within problem limits, kept moderately small for hand checking
    int D = rnd.next(5, 100);

    println(D, H, W);
    return 0;
}
