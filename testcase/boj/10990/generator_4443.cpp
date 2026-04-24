#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose a small maximum N for hand-checkable cases
    vector<int> possibleMaxN = {2, 3, 4, 5, 10};
    int maxN = rnd.any(possibleMaxN);

    // Hyper-parameter: weighting factor to skew N towards small or large
    int t = rnd.next(-2, 2);

    // Generate N in [1, maxN] with weighting
    int N = rnd.wnext(maxN, t) + 1;

    // Output
    println(N);

    return 0;
}
