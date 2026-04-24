#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of integers in input
    int N = rnd.next(1, 10);
    // Scenario: balanced, mostly positive, mostly non-positive
    int scenario = rnd.next(0, 2);
    double p;
    if (scenario == 0) {
        p = rnd.next(0.0, 1.0);
    } else if (scenario == 1) {
        p = rnd.next(0.6, 1.0);
    } else {
        p = rnd.next(0.0, 0.4);
    }
    vector<int> a;
    a.reserve(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < p) {
            // positive integer
            a.push_back(rnd.next(1, 1000000));
        } else {
            // zero or negative
            if (rnd.next() < 0.5)
                a.push_back(0);
            else
                a.push_back(rnd.next(-1000000, -1));
        }
    }
    // Shuffle to avoid any ordering bias
    shuffle(a.begin(), a.end());
    // Output as one line
    println(a);
    return 0;
}
