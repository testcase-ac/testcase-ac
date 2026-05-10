#include "testlib.h"
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

// Helper function to check maximum depth of brackets
int check_bracket_depth(const string& s) {
    int max_depth = 0;
    int cur_depth = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '[') {
            cur_depth++;
            max_depth = max(max_depth, cur_depth);
        } else if (s[i] == ']') {
            cur_depth--;
        }
    }
    return max_depth;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int tc = 0; tc < N; ++tc) {
        string vine = inf.readLine("[\\[\\]]{0,150}", "vine");
        ensuref((int)vine.size() <= 150, "Length of vine string at test case %d exceeds 150", tc+1);

        // Check only '[' and ']' are present
        for (size_t i = 0; i < vine.size(); ++i) {
            ensuref(vine[i] == '[' || vine[i] == ']', 
                "Invalid character '%c' at position %zu in test case %d", vine[i], i+1, tc+1);
        }

        // Check bracket matching and depth
        int depth = 0;
        int max_depth = 0;
        for (size_t i = 0; i < vine.size(); ++i) {
            if (vine[i] == '[') {
                depth++;
                max_depth = max(max_depth, depth);
            } else if (vine[i] == ']') {
                depth--;
                ensuref(depth >= 0, "Unmatched closing bracket at position %zu in test case %d", i+1, tc+1);
            }
        }
        ensuref(depth == 0, "Unmatched opening brackets in test case %d", tc+1);
        ensuref(max_depth <= 25, "Bracket nesting depth %d exceeds 25 in test case %d", max_depth, tc+1);
    }

    inf.readEof();
}
