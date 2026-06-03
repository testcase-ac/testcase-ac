#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> small = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.any(small);
    } else if (mode == 1) {
        n = rnd.next(3, 40);
    } else if (mode == 2) {
        n = rnd.next(1, 50) * 2;
        if (n < 4) n = 4;
    } else if (mode == 3) {
        n = rnd.next(1, 49) * 2 + 1;
        if (n < 3) n = 3;
    } else if (mode == 4) {
        n = rnd.next(900, 1000);
    } else {
        n = rnd.next(3, 1000);
    }

    println(n);
    return 0;
}
