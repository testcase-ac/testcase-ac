#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases between 3 and 7 for variety
    int T = rnd.next(3, 7);
    vector<int> Ns;

    // Always include edge cases for the first subproblem.
    Ns.push_back(1);
    Ns.push_back(20);

    // Fill remaining cases within the 10728 limit.
    for (int i = 2; i < T; i++) {
        Ns.push_back(rnd.next(2, 20));
    }

    // Shuffle to randomize order
    shuffle(Ns.begin(), Ns.end());

    // Output
    println(T);
    for (int n : Ns) {
        println(n);
    }
    return 0;
}
