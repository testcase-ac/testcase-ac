#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose k from [2,5]
    vector<int> ks = {2,3,4,5};
    int k = rnd.any(ks);
    // Hyper-parameter: interval length type
    int type = rnd.next(0, 2);
    int len;
    if (type == 0) {
        // small intervals (including point intervals)
        len = rnd.next(0, 100);
    } else if (type == 1) {
        // medium intervals
        len = rnd.next(101, 100000);
    } else {
        // large intervals
        len = rnd.next(100001, 999999999);
    }
    // Sometimes force start at 1 to test lower-bound edge
    bool startAtOne = rnd.next(0, 4) == 0;
    int l;
    if (startAtOne) {
        l = 1;
    } else {
        int maxL = 1000000000 - len;
        l = rnd.next(1, maxL);
    }
    int r = l + len;
    // Output
    println(l);
    println(r);
    println(k);
    return 0;
}
