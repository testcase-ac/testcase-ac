#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edgeValues = {0, 1, 2, 9, 10};
    int mode = rnd.next(0, 2);

    int n;
    if (mode == 0) {
        n = rnd.any(edgeValues);
    } else if (mode == 1) {
        n = rnd.next(0, 10);
    } else {
        n = rnd.next(3, 8);
    }

    println(n);
    return 0;
}
