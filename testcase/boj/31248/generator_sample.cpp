#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edgeValues = {1, 2, 3, 19, 20};
    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.any(edgeValues);
    } else if (mode == 1) {
        n = rnd.next(1, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 14);
    } else {
        n = rnd.next(15, 20);
    }

    println(n);
    return 0;
}
