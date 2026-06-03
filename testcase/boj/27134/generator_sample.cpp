#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        vector<int> possible = {3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23, 24, 27, 28, 31, 32, 35, 36, 39};
        n = rnd.any(possible);
    } else if (mode == 2) {
        vector<int> impossible = {1, 2, 5, 6, 9, 10, 13, 14, 17, 18, 21, 22, 25, 26, 29, 30, 33, 34, 37, 38};
        n = rnd.any(impossible);
    } else if (mode == 3) {
        n = rnd.next(30, 39);
    } else {
        n = rnd.next(1, 39);
    }

    println(n);
    return 0;
}
