#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose a maximum N for diversity
    vector<int> maxChoices = {5, 10, 20};
    int Nmax = rnd.any(maxChoices);

    // Small chance to force the smallest case
    double p = rnd.next();
    int N;
    if (p < 0.1) {
        N = 1;
    } else {
        N = rnd.next(2, Nmax);
    }

    // Output the single integer N
    println(N);
    return 0;
}
