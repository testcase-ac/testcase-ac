#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter to skew even count distribution
        int skew = rnd.next(-2, 2);
        // Generate number of evens E in [1,7] with weighting
        int E = rnd.wnext(7, skew) + 1;
        int O = 7 - E;
        vector<int> a;
        // Generate E even numbers in [2,100]
        for (int i = 0; i < E; ++i) {
            int x = rnd.next(1, 50) * 2;
            a.push_back(x);
        }
        // Generate O odd numbers in [1,99]
        for (int i = 0; i < O; ++i) {
            int x = rnd.next(0, 49) * 2 + 1;
            a.push_back(x);
        }
        // Shuffle to mix evens and odds
        shuffle(a.begin(), a.end());
        // Output one test case line
        println(a);
    }
    return 0;
}
