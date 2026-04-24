#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases between 1 and 10
    int T = rnd.next(1, 10);
    vector<int> Ns;
    Ns.reserve(T);

    // Generate diverse N values between 1 and 100
    for (int i = 0; i < T; i++) {
        // Hyperparameter t biases low or high values
        int t = rnd.next(-2, 2);
        int n = rnd.wnext(100, t) + 1;  // rnd.wnext(100,t) in [0,99], so +1 -> [1,100]
        Ns.push_back(n);
    }

    // Occasionally force include extremes for coverage
    if (!Ns.empty()) {
        if (rnd.next(0, 1) == 0) {
            int idx = rnd.next(0, (int)Ns.size() - 1);
            Ns[idx] = 1;
        }
        if (rnd.next(0, 1) == 0) {
            int idx = rnd.next(0, (int)Ns.size() - 1);
            Ns[idx] = 100;
        }
    }

    // Shuffle order of test cases
    shuffle(Ns.begin(), Ns.end());

    // Output each N, then a terminating 0
    for (int n : Ns) {
        println(n);
    }
    println(0);

    return 0;
}
