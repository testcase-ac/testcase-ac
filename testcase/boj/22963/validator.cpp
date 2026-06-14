#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    bool sorted = true;
    for (int i = 1; i < n; ++i) {
        if (a[i - 1] > a[i]) {
            sorted = false;
            break;
        }
    }
    ensuref(!sorted, "the sequence must not already be sorted");

    inf.readEof();
}
