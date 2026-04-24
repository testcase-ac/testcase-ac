#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    vector<int> Ns;
    // Generate diverse N values
    for (int i = 0; i < T; i++) {
        double r = rnd.next();  // in [0,1)
        int N;
        if (r < 0.1) {
            // Always include the smallest valid case
            N = 3;
        } else if (r < 0.3) {
            // Small N
            N = rnd.next(3, 10);
        } else if (r < 0.6) {
            // Medium N
            N = rnd.next(11, 1000);
        } else if (r < 0.9) {
            // Large N
            N = rnd.next(1001, 5000);
        } else {
            // Fully random
            N = rnd.next(3, 5000);
        }
        Ns.push_back(N);
    }
    // Shuffle to avoid any ordering bias
    shuffle(Ns.begin(), Ns.end());
    // Output all N values
    for (int x : Ns) {
        println(x);
    }
    return 0;
}
