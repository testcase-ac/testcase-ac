#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    set<long long> elements;
    for (int i = 0; i < N; ++i) {
        long long x = inf.readLong(0LL, 1000000000LL, "a_i");
        inf.readEoln();
        ensuref(elements.count(x) == 0, "Duplicate element detected at index %d: %lld", i+1, x);
        elements.insert(x);
    }

    inf.readEof();
}
