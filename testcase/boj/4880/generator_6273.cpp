#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(3, 8);

    // Possible differences for AP (non-zero)
    vector<int> apDs;
    for (int d = -10; d <= 10; ++d)
        if (d != 0)
            apDs.push_back(d);

    // Possible ratios for GP (integer, not -1, 0, or 1)
    vector<int> gpRs;
    for (int r = -5; r <= 5; ++r)
        if (abs(r) > 1)
            gpRs.push_back(r);

    for (int i = 0; i < T; ++i) {
        // Choose type: 0 = AP, 1 = GP
        if (rnd.next(0, 1) == 0) {
            // AP case
            int d = rnd.any(apDs);
            int a1 = rnd.next(-100, 100);
            int a2 = a1 + d;
            int a3 = a2 + d;
            println(a1, a2, a3);
        } else {
            // GP case
            int r = rnd.any(gpRs);
            int a1;
            // Ensure a1 != 0 so we don't inadvertently create zeros
            do {
                a1 = rnd.next(-50, 50);
            } while (a1 == 0);
            int a2 = a1 * r;
            int a3 = a2 * r;
            println(a1, a2, a3);
        }
    }

    // Termination line
    println(0, 0, 0);
    return 0;
}
