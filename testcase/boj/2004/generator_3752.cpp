#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose scale for n
    vector<int> scales = {20, 1000, 1000000, 2000000000};
    double r = rnd.next();
    int scale_n;
    if (r < 0.4) scale_n = scales[0];
    else if (r < 0.7) scale_n = scales[1];
    else if (r < 0.9) scale_n = scales[2];
    else scale_n = scales[3];

    // Generate n (1 to scale_n)
    int n = rnd.next(1, scale_n);

    // Hyper-parameter: distribution for m relative to n
    double r2 = rnd.next();
    int m;
    if (r2 < 0.3) {
        // m small (close to 0)
        int smallMax = max(0, n / 10);
        m = rnd.next(0, min(n, smallMax));
    } else if (r2 < 0.6) {
        // m large (close to n)
        int smallMax = max(0, n / 10);
        m = rnd.next(max(0, n - smallMax), n);
    } else {
        // m uniform in [0, n]
        m = rnd.next(0, n);
    }

    // Output
    println(n, m);
    return 0;
}
