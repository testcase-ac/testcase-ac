#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 7);
    } else if (mode == 1) {
        n = rnd.next(8, 40);
    } else if (mode == 2) {
        n = rnd.next(41, 80);
    } else if (mode == 3) {
        n = rnd.any(vector<int>{1, 2, 3, 4, 5, 6, 7, 40, 41, 79, 80});
    } else {
        n = 1 + rnd.wnext(80, rnd.any(vector<int>{-3, 0, 3}));
    }

    println(n);
    return 0;
}
