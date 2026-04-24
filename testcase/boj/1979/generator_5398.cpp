#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for biasing n toward different parts of [1,9]
    vector<int> tvals = { -2, -1, 0, 1, 2 };
    int t = rnd.any(tvals);

    // n from 1 to 9, biased by weighted next
    int n = rnd.wnext(9, t) + 1;

    // k uniformly from 1 to 9
    int k = rnd.next(1, 9);

    // Output a single test case
    println(n, k);

    return 0;
}
