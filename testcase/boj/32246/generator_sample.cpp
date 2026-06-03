#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        vector<int> edgeValues = {1, 2, 3, 4, 99, 100};
        n = rnd.any(edgeValues);
    } else if (mode == 1) {
        n = rnd.next(1, 10);
    } else if (mode == 2) {
        n = rnd.next(90, 100);
    } else if (mode == 3) {
        n = rnd.next(11, 50);
    } else if (mode == 4) {
        n = rnd.next(51, 89);
    } else {
        n = rnd.next(1, 100);
    }

    println(n);
    return 0;
}
