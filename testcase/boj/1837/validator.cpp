#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read P as a decimal string
    string P = inf.readToken("[0-9]+", "P");
    // Validate length of P
    ensuref((int)P.size() <= 100, "Length of P must be <= 100, found %d", (int)P.size());
    // Next should be a single space
    inf.readSpace();
    // Read K
    int K = inf.readInt(2, 1000000, "K");
    // End of line
    inf.readEoln();

    // Now validate that numeric value of P is at least 4
    // Strip leading zeros but leave one zero if all zeros
    int pos = 0;
    while (pos + 1 < (int)P.size() && P[pos] == '0') pos++;
    string Ps = P.substr(pos);
    // Ps is the canonical form (no leading zeros unless it's "0")
    // Check numeric >= 4
    if (Ps.size() == 1) {
        // Single digit, must be '4'..'9'
        ensuref(Ps[0] >= '4', "P must be >= 4, but found %s", P.c_str());
    }
    // If more than one digit, it's >= 10 > 4, so fine

    // Finally, ensure no extra data
    inf.readEof();
    return 0;
}
