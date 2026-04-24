#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for number of test cases
    int tParam = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int T0 = rnd.wnext(12, tParam); // results in [0,11] biased by tParam
    int T = max(1, T0);            // ensure at least one test case
    // Generate test values for n
    vector<int> ns;
    for (int i = 0; i < T; i++) {
        int wParam = rnd.any(vector<int>{-2, -1, 0, 1, 2});
        int nVal = rnd.wnext(12, wParam) + 1; // n in [1,12]
        ns.push_back(nVal);
    }
    // Shuffle order to catch ordering assumptions
    shuffle(ns.begin(), ns.end());
    // Output
    println(ns.size());
    for (int n : ns) {
        println(n);
    }
    return 0;
}
