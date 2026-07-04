#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edgeValues = {1, 2, 3, 4, 5, 10, 25, 50, 75, 100};

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.any(edgeValues);
    } else if (mode == 1) {
        n = rnd.next(1, 10);
    } else if (mode == 2) {
        n = rnd.next(11, 40);
    } else if (mode == 3) {
        n = rnd.next(41, 80);
    } else {
        n = rnd.next(81, 100);
    }

    println(n);
    return 0;
}
