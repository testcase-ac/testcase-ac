#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Precompute the maximum allowed value "10^60"
    const string MAX_K = "1" + string(60, '0');

    // Read each K and validate
    for (int i = 0; i < N; i++) {
        // Read as token of digits
        string s = inf.readToken("[0-9]+", "K");
        inf.readEoln();

        // Check length constraints
        int len = (int)s.size();
        ensuref(len >= 1 && len <= 61,
                "K[%d] has length %d but must be between 1 and 61 digits", i, len);

        // No leading zeros allowed since K >= 1
        ensuref(s[0] != '0',
                "K[%d] = %s has a leading zero", i, s.c_str());

        // If it's 61 digits, must be exactly "1" followed by 60 zeros (i.e., 10^60)
        if (len == 61) {
            ensuref(s == MAX_K,
                    "K[%d] = %s exceeds the maximum allowed value 10^60", i, s.c_str());
        }
    }

    inf.readEof();
    return 0;
}
