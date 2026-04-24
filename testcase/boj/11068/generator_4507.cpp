#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    // Some boundary values to ensure corner cases
    vector<int> boundary = {64, 65, 255, 585, 747, 1001, 1000000};

    for (int i = 0; i < T; i++) {
        double p = rnd.next();
        int n;
        if (p < 0.1) {
            // Rare boundary case
            n = rnd.any(boundary);
        } else if (p < 0.35) {
            // Small range
            n = rnd.next(64, 200);
        } else if (p < 0.7) {
            // Medium range
            n = rnd.next(201, 100000);
        } else {
            // Large range
            n = rnd.next(100001, 1000000);
        }
        println(n);
    }

    return 0;
}
