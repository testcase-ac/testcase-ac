#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> interesting = {0, 1, 2, 3, 999, 1000};
    int mode = rnd.next(0, 3);
    int n;

    if (mode == 0) {
        n = rnd.any(interesting);
    } else if (mode == 1) {
        n = rnd.next(0, 20);
    } else if (mode == 2) {
        n = rnd.next(980, 1000);
    } else {
        n = rnd.next(0, 1000);
    }

    println(n);
    return 0;
}
