#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of days
    int n = rnd.next(1, 10);
    // Maximum working days
    int m = rnd.next(0, n);
    // Wage range hyper-parameters
    int minT = rnd.next(1, 10);
    int maxT = rnd.next(minT, 100);
    // Generate wages with occasional larger spike
    vector<int> T(n);
    for (int i = 0; i < n; i++) {
        if (rnd.next(0, 9) == 0) {
            // 10% chance of a spike
            T[i] = rnd.next(maxT + 1, maxT + 50);
        } else {
            T[i] = rnd.next(minT, maxT);
        }
    }
    // Output
    println(n, m);
    println(T);
    return 0;
}
