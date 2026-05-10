#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read titles and caps
    long long prev_cap = -1;
    for (int i = 0; i < N; i++) {
        // Title name: 1 to 11 uppercase letters
        inf.readToken("[A-Z]{1,11}", "title");
        inf.readSpace();
        long long cap = inf.readLong(0LL, 1000000000LL, "cap");
        inf.readEoln();
        // Ensure non-decreasing order of caps
        ensuref(cap >= prev_cap,
                "cap at index %d is smaller than previous cap (%lld < %lld)", 
                i, cap, prev_cap);
        prev_cap = cap;
    }

    // Read queries: each power must be between 0 and prev_cap inclusive
    for (int j = 0; j < M; j++) {
        long long power = inf.readLong(0LL, prev_cap, "power");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
