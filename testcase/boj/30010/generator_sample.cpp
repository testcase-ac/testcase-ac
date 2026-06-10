#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edgeValues = {3, 4, 5, 999, 1000};
    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.any(edgeValues);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
    } else if (mode == 2) {
        n = rnd.next(13, 100);
    } else {
        n = rnd.next(101, 1000);
    }

    println(n);
    return 0;
}
