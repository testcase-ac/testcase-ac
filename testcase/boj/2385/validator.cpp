#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read N shares
    vector<string> shares;
    for (int i = 0; i < N; ++i) {
        string s = inf.readToken("[0-9]{1,5}", "share");
        shares.push_back(s);
        if (i + 1 < N)
            inf.readSpace();
        else
            inf.readEoln();
    }

    // No further global property to check:
    // - Shares can have leading zeros (see sample input 5: 2 4 11 33 00)
    // - Shares can be "0", "00", "007" (see sample input 4)
    // - It is NOT required that a valid key can be formed (see sample input 4, output is INVALID)
    // - No uniqueness required, no further global property

    inf.readEof();
}
