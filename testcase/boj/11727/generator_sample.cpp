#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        vector<int> anchors = {2, 8, 12};
        int anchor = rnd.any(anchors);
        int delta = rnd.next(-2, 2);
        n = max(1, min(1000, anchor + delta));
    } else if (mode == 2) {
        n = rnd.next(20, 120);
    } else if (mode == 3) {
        n = rnd.next(900, 1000);
    } else {
        n = rnd.next(1, 1000);
    }

    println(n);
    return 0;
}
