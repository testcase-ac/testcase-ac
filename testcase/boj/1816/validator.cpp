#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        // Read S as token to check for leading zeros
        string S = inf.readToken("[0-9]+", "S");
        inf.readEoln();

        // Check length
        ensuref(S.size() >= 12 && S.size() <= 18, 
            "S at line %d must have between 12 and 18 digits, got %zu", i+2, S.size());

        // No leading zeros allowed
        ensuref(S[0] != '0', 
            "S at line %d has leading zero", i+2);

        // Check numeric value range: 10^12 <= S <= 10^18
        // 10^12 = 1000000000000, 10^18 = 1000000000000000000
        string minS = "1000000000000";
        string maxS = "1000000000000000000";
        // Compare S >= minS
        if (S.size() > minS.size()) {
            // ok
        } else if (S.size() == minS.size()) {
            ensuref(S >= minS, "S at line %d is less than 10^12", i+2);
        } else {
            ensuref(false, "S at line %d is less than 10^12", i+2);
        }
        // Compare S <= maxS
        if (S.size() < maxS.size()) {
            // ok
        } else if (S.size() == maxS.size()) {
            ensuref(S <= maxS, "S at line %d is greater than 10^18", i+2);
        } else {
            ensuref(false, "S at line %d is greater than 10^18", i+2);
        }
    }

    inf.readEof();
}
