#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for length distribution
    double r = rnd.next();
    int L;
    if (r < 0.2) L = 1;
    else if (r < 0.5) L = rnd.next(2, 5);
    else L = rnd.next(6, 10);

    // Hyper-parameter for maximum value
    double s = rnd.next();
    int maxVal;
    if (s < 0.3) maxVal = 10000;
    else if (s < 0.6) maxVal = rnd.next(100, 500);
    else maxVal = rnd.next(10, 100);

    // Generate the sequence
    vector<int> a;
    for (int i = 0; i < L; i++) {
        a.push_back(rnd.next(1, maxVal));
    }

    // Output in one line
    println(a);
    return 0;
}
