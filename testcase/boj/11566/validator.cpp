#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n
    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    // 2. Read n notes (reality)
    vector<int> reality = inf.readInts(n, 1, 1000000000, "reality_notes");
    inf.readEoln();

    // 3. Read m
    int m = inf.readInt(n, 1000, "m");
    inf.readEoln();

    // 4. Read m notes (dream)
    vector<int> dream = inf.readInts(m, 1, 1000000000, "dream_notes");
    inf.readEoln();

    // 5. Check for extra input
    inf.readEof();

    // 6. Additional checks (none required by problem)
    // - n >= 2, m >= n, m <= 1000, all notes in [1, 1e9]
    // - No further global properties to check (e.g., uniqueness, order, etc.)
    // - Duplicates are allowed, order is arbitrary, values can repeat.

    return 0;
}
