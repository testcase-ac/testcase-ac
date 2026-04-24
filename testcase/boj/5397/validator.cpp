#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read the logged keys string: must consist only of uppercase, lowercase, digits, '-', '<', '>'
        // and length between 1 and 1e6.
        string s = inf.readLine("[A-Za-z0-9<>-]+", "keys");
        int L = (int)s.size();
        ensuref(L >= 1 && L <= 1000000,
                "Length of keys in test case %d is %d, but should be in [1,1000000]", 
                tc, L);

        // Simulate the editing process using two stacks (left and right of the cursor).
        // This runs in O(L) time and O(L) memory.
        vector<char> left, right;
        left.reserve(L);
        right.reserve(L);

        for (char c : s) {
            if (c == '-') {
                if (!left.empty()) {
                    left.pop_back();
                }
            } else if (c == '<') {
                if (!left.empty()) {
                    right.push_back(left.back());
                    left.pop_back();
                }
            } else if (c == '>') {
                if (!right.empty()) {
                    left.push_back(right.back());
                    right.pop_back();
                }
            } else {
                // A valid ordinary character: insert at cursor
                left.push_back(c);
            }
        }

        // The final password length must be > 0 as guaranteed by the problem
        long long final_len = (long long)left.size() + (long long)right.size();
        ensuref(final_len > 0,
                "Final password length is %d in test case %d, but should be > 0",
                (int)final_len, tc);
    }

    inf.readEof();
    return 0;
}
