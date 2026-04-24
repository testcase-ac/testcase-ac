#include "testlib.h"
#include <string>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read initial string S: only letters, length between 1 and 100000
    string S = inf.readToken("[A-Za-z]{1,100000}", "S");
    int Slen = (int)S.size();

    // Read n: number of queries, between 1 and 300000
    inf.readSpace();
    int n = inf.readInt(1, 300000, "n");
    inf.readEoln();

    long long countType2 = 0;
    for (int i = 0; i < n; i++) {
        // Each query starts with a type 1 or 2
        int tp = inf.readInt(1, 2, "type");
        if (tp == 1) {
            // Format: 1 i1 i2
            inf.readSpace();
            // i1: a single letter
            inf.readToken("[A-Za-z]", "i1");
            inf.readSpace();
            // i2: a single letter
            inf.readToken("[A-Za-z]", "i2");
            inf.readEoln();
        } else {
            // Format: 2
            inf.readEoln();
            countType2++;
        }
    }

    // There must be at least one type-2 query
    ensuref(countType2 >= 1, "There must be at least one query of type 2");

    // Total characters printed by type-2 queries = countType2 * |S|
    // Must not exceed 10^7
    __int128 totalPrinted = (__int128)countType2 * Slen;
    ensuref(totalPrinted <= 10000000LL,
            "Total output characters (%lld) exceed 1e7",
            (long long)totalPrinted);

    inf.readEof();
    return 0;
}
