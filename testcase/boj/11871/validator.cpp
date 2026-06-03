#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    vector<long long> p = inf.readLongs(n, 1LL, 2147000000LL, "P_i");
    inf.readEoln();

    bool allTwo = true;
    for (int i = 0; i < n; ++i) {
        if (p[i] != 2) {
            allTwo = false;
        }
    }
    ensuref(!allTwo, "all P_i are 2");

    inf.readEof();
}
