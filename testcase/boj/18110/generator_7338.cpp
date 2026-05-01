#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Occasionally test the no-op case n=0
    if (rnd.next() < 0.1) {
        println(0);
        return 0;
    }
    // Generate n between 1 and 30 for hand-checkable size
    int n = rnd.next(1, 30);
    println(n);
    // Choose a distribution: 0 = uniform, 1 = skew low, 2 = skew high
    int dist = rnd.next(0, 2);
    for (int i = 0; i < n; i++) {
        int val;
        if (dist == 0) {
            // Uniform opinions
            val = rnd.next(1, 30);
        } else if (dist == 1) {
            // Skew towards low values
            val = rnd.wnext(30, -2) + 1;
        } else {
            // Skew towards high values
            val = rnd.wnext(30, 2) + 1;
        }
        println(val);
    }
    return 0;
}
