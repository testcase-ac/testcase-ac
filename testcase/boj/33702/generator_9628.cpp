#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int K;
    int mode = rnd.next(0, 4); // choose generation mode

    if (mode == 0) {
        // Center start, often interesting
        K = 5;
    } else if (mode == 1) {
        // Corner starts
        vector<int> corners = {1, 3, 7, 9};
        K = rnd.any(corners);
    } else if (mode == 2) {
        // Edge (non-corner) starts
        vector<int> edges = {2, 4, 6, 8};
        K = rnd.any(edges);
    } else if (mode == 3) {
        // Completely uniform random
        K = rnd.next(1, 9);
    } else {
        // Explicitly force a sample with known tricky behavior from statement
        K = 8;
    }

    println(K);
    return 0;
}
