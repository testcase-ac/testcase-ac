#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    vector<int> ns;

    // Ensure a variety: one small, one medium, one near the upper bound
    if (T >= 1) ns.push_back(rnd.next(1, 5));
    if (T >= 2) ns.push_back(rnd.next(6, 20));
    if (T >= 3) ns.push_back(rnd.next(99000, 100000));

    // Fill the rest with a mix of small- and large-skewed values
    for (int i = (int)ns.size(); i < T; ++i) {
        if (rnd.next(0, 1) == 0) {
            // skewed towards small numbers
            ns.push_back(rnd.wnext(100000, -2) + 1);
        } else {
            // skewed towards large numbers
            ns.push_back(rnd.wnext(100000, 2) + 1);
        }
    }

    // Randomize the order of test cases
    shuffle(ns.begin(), ns.end());

    // Output
    println(T);
    for (int n : ns) {
        println(n);
    }

    return 0;
}
