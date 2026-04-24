#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 3);
    int N, M;
    if (type == 0) {
        // single row
        N = 1;
        M = rnd.next(1, 300);
    } else if (type == 1) {
        // single column
        N = rnd.next(1, 300);
        M = 1;
    } else if (type == 2) {
        // squareish shape
        int side = rnd.next(1, 17);
        N = side;
        M = rnd.next(1, 300 / side);
    } else {
        // general rectangle
        int area = rnd.next(1, 300);
        N = rnd.next(1, area);
        int maxM = area / N;
        if (maxM < 1) maxM = 1;
        M = rnd.next(1, maxM);
    }

    println(N, M);
    return 0;
}
