#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        // Read N as a token (since up to 10^18)
        string Nstr = inf.readToken("[0-9]{1,18}", "N");
        // Check for leading zeros
        ensuref(Nstr.size() == 1 || Nstr[0] != '0', 
            "Leading zeros in N at test case %d: '%s'", tc, Nstr.c_str());

        // Check range 1 <= N <= 10^18
        // (since Nstr is at most 18 digits, and no leading zeros, we can compare as string)
        string maxN = "1000000000000000000";
        ensuref(Nstr.size() < maxN.size() || (Nstr.size() == maxN.size() && Nstr <= maxN),
            "N out of range at test case %d: '%s'", tc, Nstr.c_str());

        inf.readEoln();
    }

    inf.readEof();
}
