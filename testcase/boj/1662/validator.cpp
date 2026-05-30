#include "testlib.h"
#include <string>
#include <stack>
#include <cassert>
using namespace std;

constexpr long long kMaxDecompressedLength = 2147473647LL;

// Returns the decompressed length of s[l, r)
long long decompress_length(const string& s, int l, int r) {
    long long total = 0;
    int i = l;
    while (i < r) {
        if ('0' <= s[i] && s[i] <= '9') {
            // Check if this is a K(Q) pattern
            if (i + 1 < r && s[i + 1] == '(') {
                int K = s[i] - '0';
                int j = i + 2;
                int open = 1;
                int start = j;
                // Find the matching ')'
                while (j < r && open > 0) {
                    if (s[j] == '(') open++;
                    else if (s[j] == ')') open--;
                    j++;
                }
                ensuref(open == 0, "Unmatched '(' at position %d", i + 1);
                // s[start, j-1) is Q
                long long len = decompress_length(s, start, j - 1);
                ensuref(len >= 0, "Negative length in decompression");
                // Check for overflow
                __int128_t prod = (__int128_t)K * (__int128_t)len;
                ensuref(prod <= kMaxDecompressedLength,
                        "Decompressed length exceeds 2,147,473,647 at position %d", i);
                total += (long long)prod;
                ensuref(total <= kMaxDecompressedLength,
                        "Total decompressed length exceeds 2,147,473,647");
                i = j;
            } else {
                // Just a digit, counts as 1
                total++;
                ensuref(total <= kMaxDecompressedLength,
                        "Total decompressed length exceeds 2,147,473,647");
                i++;
            }
        } else if (s[i] == '(' || s[i] == ')') {
            // Parentheses outside K(Q) are not allowed
            ensuref(false, "Parenthesis at position %d not part of K(Q) pattern", i);
        } else {
            ensuref(false, "Invalid character '%c' at position %d", s[i], i);
        }
    }
    return total;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the compressed string S
    string S = inf.readToken("[0-9()]{1,50}", "S");
    inf.readEoln();

    // Check that S contains only '0'-'9', '(' and ')'
    for (size_t i = 0; i < S.size(); ++i) {
        char c = S[i];
        ensuref((c >= '0' && c <= '9') || c == '(' || c == ')',
            "Invalid character '%c' at position %zu", c, i);
    }

    // Check that parentheses are balanced and only appear as part of K(Q)
    int n = S.size();
    stack<int> paren_stack;
    for (int i = 0; i < n; ++i) {
        if (S[i] == '(') {
            // Must be immediately after a digit (K)
            ensuref(i > 0 && (S[i-1] >= '0' && S[i-1] <= '9'),
                "Parenthesis '(' at position %d not immediately after a digit", i);
            paren_stack.push(i);
        } else if (S[i] == ')') {
            ensuref(!paren_stack.empty(), "Unmatched ')' at position %d", i);
            int open_idx = paren_stack.top(); paren_stack.pop();
            // The matching '(' must be after a digit (already checked above)
            // No further check needed here
        }
    }
    ensuref(paren_stack.empty(), "Unmatched '(' at position %d", paren_stack.empty() ? -1 : paren_stack.top());

    // Check that all K(Q) patterns have K as a single digit, and Q can be empty or any valid substring
    // (Already enforced by the above checks and the decompress_length function)

    // Check decompressed length is <= 2,147,473,647 and does not overflow during computation
    decompress_length(S, 0, S.size());

    inf.readEof();
}
