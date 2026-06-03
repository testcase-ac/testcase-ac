#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edgeCases = {1, 2, 9, 10, 11, 40, 99, 100};
    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.any(edgeCases);
    } else if (mode == 1) {
        n = rnd.next(1, 15);
    } else if (mode == 2) {
        n = rnd.next(16, 50);
    } else {
        n = rnd.next(51, 100);
    }

    println(n);
    return 0;
}
