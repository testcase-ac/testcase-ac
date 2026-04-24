#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read counts of participants
    int b = inf.readInt(0, 100000, "b");
    inf.readSpace();
    int n = inf.readInt(0, 100000, "n");
    inf.readSpace();
    int e = inf.readInt(0, 100000, "e");
    inf.readEoln();

    // Total participants must be even, at least 2, and at most 100000
    long long total = (long long)b + n + e;
    ensuref(total >= 2 && total <= 100000 && total % 2 == 0,
            "Total participants (b + n + e) = %lld must be even, at least 2, and at most 100000", total);

    // Read strengths
    int s_b = inf.readInt(1, 1000, "s_b");
    inf.readSpace();
    int s_n = inf.readInt(1, 1000, "s_n");
    inf.readSpace();
    int s_e = inf.readInt(1, 1000, "s_e");
    inf.readEoln();
    ensuref(s_b < s_n && s_n < s_e,
            "Strengths must satisfy s_b < s_n < s_e, got s_b=%d, s_n=%d, s_e=%d", s_b, s_n, s_e);

    // Number of kayaks
    int m = total / 2;
    // Read speed factors
    vector<int> c = inf.readInts(m, 1, 100000, "c_i");
    inf.readEoln();

    // End of file
    inf.readEof();

    return 0;
}
