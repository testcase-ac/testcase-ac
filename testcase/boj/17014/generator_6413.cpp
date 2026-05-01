#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small enough for manual verification
    int T = rnd.next(1, 30);
    vector<int> Ns;

    if (T == 1) {
        // Single random N
        Ns.push_back(rnd.next(4, 1000000));
    } else {
        // Ensure boundary cases are present
        Ns.push_back(4);
        Ns.push_back(1000000);
        // Generate the rest with diverse sizes
        for (int i = 2; i < T; i++) {
            double p = rnd.next();
            if (p < 0.15) {
                // Very small edge cases
                vector<int> smalls = {4, 5, 6, 7, 8, 9, 10};
                Ns.push_back(rnd.any(smalls));
            } else if (p < 0.45) {
                // Small to medium
                Ns.push_back(rnd.next(4, 1000));
            } else if (p < 0.80) {
                // Medium to moderately large
                Ns.push_back(rnd.next(1001, 100000));
            } else {
                // Large values
                Ns.push_back(rnd.next(100001, 1000000));
            }
        }
    }

    // Shuffle to mix boundary and random cases
    shuffle(Ns.begin(), Ns.end());

    // Output
    println(Ns.size());
    for (int n : Ns) {
        println(n);
    }

    return 0;
}
