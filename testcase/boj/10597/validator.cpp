#include "testlib.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input line (the only line in the input)
    string s = inf.readLine("[0-9]{1,1000}", "s"); // up to 50 numbers, each up to 2 digits, so max 100 chars, but allow up to 1000 for safety

    // Check that s is not empty
    ensuref(!s.empty(), "Input string is empty");

    // Check that s contains only digits (already enforced by regex, but double-check)
    for (size_t i = 0; i < s.size(); ++i) {
        ensuref(isdigit(s[i]), "Non-digit character at position %zu", i);
    }

    // Now, check that s can be split into a permutation of 1..N, for some N in [1,50]
    // Each number is in [1,N], all numbers are unique, and concatenation in order gives s

    // Try all possible N in [1,50]
    bool possible = false;
    for (int N = 1; N <= 50; ++N) {
        // Prepare set of numbers as strings
        set<string> nums;
        for (int i = 1; i <= N; ++i) nums.insert(to_string(i));

        // Try to split s greedily (backtracking)
        vector<string> result;
        set<string> used;

        // Memoization to avoid repeated work: pos, used mask
        // But since N is small, just do simple backtracking

        function<bool(size_t)> dfs = [&](size_t pos) -> bool {
            if (pos == s.size()) {
                return result.size() == (size_t)N;
            }
            // Try 1 or 2 digit numbers (since N<=50, max 2 digits)
            for (int len = 1; len <= 2 && pos + len <= s.size(); ++len) {
                string token = s.substr(pos, len);
                if (nums.count(token) && !used.count(token)) {
                    used.insert(token);
                    result.push_back(token);
                    if (dfs(pos + len)) return true;
                    result.pop_back();
                    used.erase(token);
                }
            }
            return false;
        };

        if (dfs(0)) {
            possible = true;
            break;
        }
    }

    ensuref(possible, "Input string cannot be split into a permutation of 1..N for any N in [1,50]");

    inf.readEof();
}
