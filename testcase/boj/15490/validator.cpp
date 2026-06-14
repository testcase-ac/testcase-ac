#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 2147483647, "a_i");
    inf.readEoln();

    int odd_count = 0;
    for (int i = 0; i < n; ++i) {
        odd_count += a[i] % 2;
    }
    ensuref(odd_count % 2 == 1, "number of odd elements must be odd, got %d", odd_count);

    inf.readEof();
}
