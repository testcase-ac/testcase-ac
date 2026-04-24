#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small N for hand-checkability
    int N = rnd.next(1, 10);
    // Mode for density: -1 sparse, 0 uniform, +1 dense
    int mode = rnd.next(-1, 1);
    double density;
    if (mode < 0) {
        // skew towards 0
        density = rnd.wnext(101, -1) / 100.0;
    } else if (mode == 0) {
        // uniform
        density = rnd.next();
    } else {
        // skew towards 1
        density = rnd.wnext(101, 1) / 100.0;
    }
    // Build the first-row string
    string s;
    s.reserve(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < density)
            s.push_back('#');
        else
            s.push_back('.');
    }
    // Output the generated input
    println(N);
    println(s);
    return 0;
}
