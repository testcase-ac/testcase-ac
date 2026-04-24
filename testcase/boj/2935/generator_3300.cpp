#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: maximum number of zeros for powers of 10
    vector<int> maxZerosChoices = {0, 1, 2, 5, 10};
    int maxZeros = rnd.any(maxZerosChoices);

    // Weight parameters to skew lengths
    int t1 = rnd.next(-3, 3);
    int t2 = rnd.next(-3, 3);

    // Sample exponents for A and B in [0, maxZeros]
    int k1 = rnd.wnext(maxZeros + 1, t1);
    int k2 = rnd.wnext(maxZeros + 1, t2);

    // Choose operator
    char op = (rnd.next(2) == 0 ? '+' : '*');

    // Build numbers as strings: "1" followed by k zeros
    string A = "1" + string(k1, '0');
    string B = "1" + string(k2, '0');

    // Output test case
    println(A);
    println(op);
    println(B);

    return 0;
}
