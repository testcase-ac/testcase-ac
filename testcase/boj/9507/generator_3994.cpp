#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small and hand-checkable
    int t = rnd.next(5, 10);

    vector<int> ns;
    // Always include extreme cases
    ns.push_back(0);
    ns.push_back(67);

    // Fill the rest with diverse n values using weighted randomness
    while ((int)ns.size() < t) {
        // weight from -2 to 2: negative biases to small, positive to large
        int weight = rnd.next(-2, 2);
        int n = rnd.wnext(68, weight); // gives [0,67]
        ns.push_back(n);
    }

    // Shuffle the test cases so extremes aren't always first
    shuffle(ns.begin(), ns.end());

    // Output
    println(t);
    for (int x : ns) {
        println(x);
    }

    return 0;
}
