#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edges = {1, 2, 3, 4, 5, 10, 50, 199999, 200000};
    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.any(edges);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 500);
    } else if (mode == 3) {
        n = rnd.next(1000, 10000);
    } else {
        n = rnd.next(190000, 200000);
    }

    println(n);
    return 0;
}
