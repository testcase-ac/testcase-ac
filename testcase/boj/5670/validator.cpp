#include "testlib.h"
#include <string>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseNum = 0;
    // Read test cases until EOF
    while (!inf.eof()) {
        ++caseNum;
        setTestCase(caseNum);

        // Read N
        int N = inf.readInt(1, 100000, "N");
        inf.readEoln();

        // Validate dictionary words
        long long totalLen = 0;
        unordered_set<string> seen;
        seen.reserve(N);
        for (int i = 0; i < N; i++) {
            // a word: 1 to 80 lowercase letters
            string w = inf.readToken("[a-z]{1,80}", "word");
            inf.readEoln();

            // No duplicates
            bool inserted = seen.insert(w).second;
            ensuref(inserted,
                    "Duplicate word in test case %d: \"%s\"",
                    caseNum, w.c_str());

            totalLen += (int)w.size();
        }

        // Sum of lengths in this test case ≤ 1e6
        ensuref(totalLen <= 1000000LL,
                "Sum of word lengths in test case %d is too large: %lld (max 1000000)",
                caseNum, totalLen);
    }

    // Number of test cases ≤ 100000
    ensuref(caseNum <= 100000,
            "Too many test cases: %d (max 100000)",
            caseNum);

    inf.readEof();
    return 0;
}
