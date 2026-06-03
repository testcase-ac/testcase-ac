#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int b;

    if (mode == 0) {
        vector<int> bounds = {1100, 9900};
        b = rnd.any(bounds);
    } else if (mode == 1) {
        int a = rnd.next(10, 90) * 100;
        b = a / 10 * 11;
    } else if (mode == 2) {
        b = rnd.next(100, 900) * 11;
    } else {
        int a = rnd.next(10, 90) * 100;
        b = a + a / 10;
    }

    println(b);
    return 0;
}
