#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> nValues = {0, 1, 2, 3, 4, 5};
    vector<int> wValues = {0, 1, 999, 1000, 1001, 1999, 2000};

    int mode = rnd.next(0, 4);
    int N;
    int W;

    if (mode == 0) {
        N = rnd.next(0, 5);
        W = rnd.next(0, 2000);
    } else if (mode == 1) {
        N = rnd.any(nValues);
        W = rnd.next(0, 2000);
    } else if (mode == 2) {
        N = rnd.next(0, 5);
        W = rnd.any(wValues);
    } else {
        N = rnd.any(nValues);
        W = rnd.any(wValues);
    }

    println(N);
    println(W);

    return 0;
}
