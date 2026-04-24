#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checkable cases
    int N = rnd.next(1, 10);

    // Hyper-parameter: bias towards following the drinking cycle
    // We sample a weight t in [-2,2] to bias p towards 0 or 1
    int t = rnd.next(-2, 2);
    double p = rnd.wnext(101, t) / 100.0;  // probability to follow expected next milk

    vector<int> a;
    a.reserve(N);
    int expect = 0; // starts wanting strawberry (0)
    for (int i = 0; i < N; i++) {
        if (rnd.next() < p) {
            // follow the expected cycle
            a.push_back(expect);
            expect = (expect + 1) % 3;
        } else {
            // random milk shop type
            a.push_back(rnd.next(0, 2));
        }
    }

    // Output format
    println(N);
    println(a);

    return 0;
}
