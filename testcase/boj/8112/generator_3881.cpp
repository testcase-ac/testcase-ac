#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    vector<int> ns;
    
    // Ensure diverse edge cases if space allows
    if (T >= 1) {
        // N = 1
        ns.push_back(1);
    }
    if (T >= 2) {
        // Even N
        int x = rnd.next(1, 500);
        ns.push_back(x * 2);
    }
    if (T >= 3) {
        // Multiple of 5
        int y = rnd.next(1, 200);
        ns.push_back(y * 5);
    }
    // Fill the rest with mixed sizes
    for (int i = ns.size(); i < T; i++) {
        int type = rnd.next(0, 2);
        if (type == 0) {
            // Small N
            ns.push_back(rnd.next(1, 20));
        } else if (type == 1) {
            // Medium N
            ns.push_back(rnd.next(21, 200));
        } else {
            // Large N
            ns.push_back(rnd.next(201, 1000000));
        }
    }

    // Shuffle for randomness
    shuffle(ns.begin(), ns.end());

    // Output
    println(T);
    for (int n : ns) {
        println(n);
    }

    return 0;
}
