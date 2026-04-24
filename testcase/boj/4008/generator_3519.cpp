#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of soldiers
    int n = rnd.next(1, 10);

    // Coefficients a < 0, b, c
    int a = rnd.next(-5, -1);
    int b = (rnd.next() < 0.5 ? 0 : rnd.next(-20, 20));
    int c = (rnd.next() < 0.5 ? 0 : rnd.next(-20, 20));

    // Hyper-parameter for x distribution: uniform, biased low, biased high
    int mode = rnd.next(0, 2);
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        if (mode == 0) {
            // pure uniform 1..10
            x[i] = rnd.next(1, 10);
        } else if (mode == 1) {
            // bias towards 1
            x[i] = (rnd.next() < 0.3 ? 1 : rnd.next(1, 10));
        } else {
            // bias towards 10
            x[i] = (rnd.next() < 0.3 ? 10 : rnd.next(1, 10));
        }
    }

    // Output
    println(n);
    println(a, b, c);
    println(x);

    return 0;
}
