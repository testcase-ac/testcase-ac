#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size N between 2 and 10 for hand-checkable sizes
    int N = rnd.next(2, 10);
    // k is either 0 or 1
    int k = rnd.next(0, 1);
    println(N, k);
    // Generate grid with some bias for variability
    for (int i = 0; i < N; i++) {
        vector<int> row(N);
        for (int j = 0; j < N; j++) {
            double p = rnd.next();
            if (p < 0.2) {
                // biased sampling: t in [-3,3], wnext skews distribution
                int t = rnd.next(-3, 3);
                row[j] = rnd.wnext(6, t);
            } else {
                // uniform random tile type in [0,5]
                row[j] = rnd.next(0, 5);
            }
        }
        println(row);
    }
    return 0;
}
