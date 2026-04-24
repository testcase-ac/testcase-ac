#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    vector<int> sizes(T);
    // Fill with random sizes between 1 and 10
    for (int i = 0; i < T; i++) {
        sizes[i] = rnd.next(1, 10);
    }
    // Hyper-parameter to force an extreme case
    double mode = rnd.next(0.0, 1.0);
    if (mode < 0.3) {
        // ensure a minimal box
        sizes[0] = 1;
    } else if (mode < 0.6) {
        // ensure a maximal box
        sizes[0] = 10;
    }
    // Maybe shuffle order to mix edge cases
    if (rnd.next(0,1)) {
        shuffle(sizes.begin(), sizes.end());
    }

    // Output
    println(T);
    for (int x: sizes) {
        println(x);
    }
    return 0;
}
