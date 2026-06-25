#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(4, 10);
    } else if (mode == 1) {
        vector<int> sampleNeighbors = {4, 5, 6, 29, 30, 31};
        n = rnd.any(sampleNeighbors);
    } else if (mode == 2) {
        n = rnd.next(11, 60);
    } else if (mode == 3) {
        n = rnd.next(61, 150);
    } else if (mode == 4) {
        n = rnd.next(151, 299);
    } else {
        n = 300;
    }

    println(n);
    return 0;
}
