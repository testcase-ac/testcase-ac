#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edgeValues = {1, 2, 3, 13, 14};
    int mode = rnd.next(0, 2);
    int n;
    if (mode == 0) {
        n = rnd.any(edgeValues);
    } else if (mode == 1) {
        n = rnd.next(1, 14);
    } else {
        n = rnd.next(1, 7) * 2 - rnd.next(0, 1);
    }

    println(n);
    return 0;
}
