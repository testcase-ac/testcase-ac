#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diverse n
    vector<string> modes = {"uniform", "low", "high", "edge"};
    string mode = rnd.any(modes);

    int n;
    if (mode == "uniform") {
        // Uniform over all valid n
        n = rnd.next(1, 116);
    } else if (mode == "low") {
        // Biased towards small n (base cases)
        n = rnd.wnext(116, -3) + 1;  // range 1..116, biased low
    } else if (mode == "high") {
        // Biased towards large n (stress values)
        n = rnd.wnext(116, 3) + 1;   // range 1..116, biased high
    } else {
        // Edge cases
        vector<int> edges = {1, 2, 3, 116};
        n = rnd.any(edges);
    }

    // Output single test case
    println(n);
    return 0;
}
