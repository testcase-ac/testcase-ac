#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of planets
    int n = inf.readInt(3, 100000, "n");
    inf.readEoln();

    // Read distances between adjacent planets: exactly one line with n-1 integers
    vector<int> d(n-1);
    for (int i = 0; i < n-1; i++) {
        d[i] = inf.readInt(1, 1000, "d_i");
        if (i < n-2) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // Read preparation time and spaceship pace for planets 1 to n-1
    for (int i = 1; i <= n-1; i++) {
        long long p = inf.readLong(0LL, 1000000000LL, "p_i");
        inf.readSpace();
        int s = inf.readInt(1, 100000, "s_i");
        inf.readEoln();
        // No additional cross-checks needed since each line stands alone
    }

    inf.readEof();
    return 0;
}
