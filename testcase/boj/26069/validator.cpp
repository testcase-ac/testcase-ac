#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of records
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    const string CHONG = "ChongChong";
    bool seenChong = false;

    // Validate each meeting record
    for (int i = 0; i < N; i++) {
        // Read two names: A_i and B_i
        string A = inf.readToken("[0-9A-Za-z]{1,20}", "A_i");
        inf.readSpace();
        string B = inf.readToken("[0-9A-Za-z]{1,20}", "B_i");
        inf.readEoln();

        // They must be distinct persons
        ensuref(A != B,
                "Record %d has identical names: '%s' and '%s'",
                i+1, A.c_str(), B.c_str());

        // Check if ChongChong appears
        if (A == CHONG || B == CHONG) {
            seenChong = true;
        }
    }

    // Ensure ChongChong appears at least once
    ensuref(seenChong,
            "ChongChong must appear in at least one record");

    inf.readEof();
    return 0;
}
