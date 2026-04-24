#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 15, "N");
    inf.readEoln();

    // Read the N distinct natural numbers (length <= 50, no leading zeros)
    set<string> seen;
    for (int i = 0; i < N; i++) {
        // regex: first digit 1-9, then up to 49 digits 0-9 => length 1 to 50, no leading zeros
        string s = inf.readToken("[1-9][0-9]{0,49}", "number");
        inf.readEoln();
        // ensure distinct
        bool inserted = seen.insert(s).second;
        ensuref(inserted, "Duplicate number: %s", s.c_str());
    }

    // Read K
    int K = inf.readInt(1, 100, "K");
    inf.readEoln();

    inf.readEof();
    return 0;
}
