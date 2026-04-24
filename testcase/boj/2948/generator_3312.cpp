#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Special edge-case hyper-parameter for fixed dates
    int mode = rnd.next(1, 5);
    int D, M;
    if (mode == 1) {
        M = 1; D = 1;      // Jan 1
    } else if (mode == 2) {
        M = 12; D = 31;    // Dec 31
    } else if (mode == 3) {
        M = 2; D = 28;     // Feb 28 (end of Feb)
    } else {
        // Biased random generation
        vector<int> ts = {-2, -1, 0, 1, 2};
        int tM = rnd.any(ts);
        M = rnd.wnext(12, tM) + 1;  // month in [1,12] with bias

        // Days per month in 2009 (not leap)
        vector<int> mdays = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int daysInM = mdays[M];

        int tD = rnd.any(ts);
        D = rnd.wnext(daysInM, tD) + 1;  // day in [1, daysInM] with bias
    }

    // Output format: D M
    println(D, M);
    return 0;
}
