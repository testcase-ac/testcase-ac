#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edgeCases = {1, 2, 3, 4, 5, 10, 50, 99, 100};
    int mode = rnd.next(0, 3);
    int n;

    if (mode == 0) {
        n = rnd.any(edgeCases);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
    } else if (mode == 2) {
        n = rnd.next(13, 60);
    } else {
        n = rnd.next(61, 100);
    }

    println(n);
    return 0;
}
