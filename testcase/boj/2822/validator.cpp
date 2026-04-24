#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There is exactly one test: 8 lines follow, each with one integer score.
    const int L = 0;
    const int R = 150;
    vector<int> scores;
    scores.reserve(8);

    for (int i = 0; i < 8; i++) {
        // Read the i-th score: one integer in [0,150]
        char buf[20];
        snprintf(buf, sizeof(buf), "score_%d", i+1);
        int s = inf.readInt(L, R, buf);
        // After the integer, there must be exactly end of line
        inf.readEoln();
        scores.push_back(s);
    }

    // Check that all 8 scores are distinct
    set<int> st(scores.begin(), scores.end());
    ensuref((int)st.size() == 8,
            "Duplicate scores detected: expected 8 distinct values, got %d distinct", (int)st.size());

    // No more input
    inf.readEof();
    return 0;
}
