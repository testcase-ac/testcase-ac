#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of words N
    int n = inf.readInt(1, 10, "N");
    inf.readEoln();

    // Track distinct uppercase letters across all words
    vector<bool> seen(26, false);
    int distinct = 0;

    // Read each word
    for (int i = 0; i < n; i++) {
        // Each word: only uppercase letters, length 1 to 8
        string name = string("word_") + to_string(i+1);
        string s = inf.readToken("[A-Z]{1,8}", name.c_str());
        inf.readEoln();

        // Count distinct letters
        for (char c : s) {
            int idx = c - 'A';
            if (!seen[idx]) {
                seen[idx] = true;
                distinct++;
            }
        }
    }

    // Validate the global constraint: at most 10 distinct letters
    ensuref(distinct <= 10,
            "Number of distinct letters is %d, but must be <= 10", distinct);

    inf.readEof();
    return 0;
}
