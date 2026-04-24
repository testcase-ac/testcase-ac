#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small for hand checking
    int T = rnd.next(1, 10);

    vector<int> Ns;
    // Include small edge cases
    Ns.push_back(1);
    if (T >= 2) Ns.push_back(2);
    // Fill the rest with random N in [3,10]
    for (int i = (int)Ns.size(); i < T; ++i) {
        Ns.push_back(rnd.next(3, 10));
    }
    // Shuffle to mix edge cases and random ones
    shuffle(Ns.begin(), Ns.end());

    // Output
    println(T);
    for (int n : Ns) {
        println(n);
    }
    return 0;
}
