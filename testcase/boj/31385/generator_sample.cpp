#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edgeValues = {2, 3, 4, 5, 10, 100, 99999, 100000};
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.any(edgeValues);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
    } else if (mode == 2) {
        int base = rnd.next(95, 105);
        n = rnd.next(max(2, base - 5), base + 5);
    } else if (mode == 3) {
        n = rnd.next(990, 1010);
    } else if (mode == 4) {
        n = rnd.next(99980, 100000);
    } else {
        n = rnd.next(2, 100000);
    }

    println(n);
    return 0;
}
