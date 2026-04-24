#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    vector<int> ns;
    ns.reserve(T);
    for (int i = 0; i < T; i++) {
        double p = rnd.next(0.0, 1.0);
        int n;
        if (p < 0.3) {
            // small
            n = rnd.next(1, 10);
        } else if (p < 0.6) {
            // medium
            n = rnd.next(11, 1000);
        } else {
            // large
            n = rnd.next(1001, 1000000);
        }
        ns.push_back(n);
    }
    // Shuffle order of test cases for diversity
    shuffle(ns.begin(), ns.end());
    // Output
    println(T);
    for (int x : ns) {
        println(x);
    }
    return 0;
}
