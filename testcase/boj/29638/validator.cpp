#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<long long> bottles(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        bottles[i] = inf.readLong(1LL, 1000000000LL, format("a[%d]", i + 1).c_str());
    }
    inf.readEoln();

    inf.readEof();
}
