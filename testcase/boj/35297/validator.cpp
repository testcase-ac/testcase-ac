#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
 Problem (for validator):

 - Input: single line string X
 - Constraints:
     1 <= |X| <= 5 * 10^5
     X_i ∈ {'K','S','A'}
 - Guarantee in statement:
     "주어진 시행을 유한 번 하는 것으로 문자열 X를
      X와 길이가 같으면서 KSAAC 운영진이 좋아하는 문자열로
      바꿀 수 있음이 보장된다."

 Operations:
   1) Remove two adjacent characters.
   2) Add two identical characters to the front.

 A "liked" string Y of length n is uniquely defined by:
   for i from 1..n (1-based):
     i % 3 == 1 -> 'K'
     i % 3 == 2 -> 'S'
     i % 3 == 0 -> 'A'

 From the previous failed attempt we know:
   - Simply checking a naive invariant such as per-character parity
     against the target pattern is *not* implied by the statement,
     because the official samples (e.g. "KKK") violate that check
     yet are valid inputs.

 Therefore:
   - From validator's perspective, the *only* global property we must
     enforce is exactly what is *explicitly* promised by the statement.
   - The promise is: for any test used, it must be possible to transform
     X into the liked string of the same length via the operations.
   - However, the problem statement does not provide a clear, simple
     necessary-and-sufficient structural condition for that reachability,
     and our previous attempt at "proving" and encoding one was incorrect
     (demonstrated by contradicting the official sample).
   - We must not guess or enforce unproven invariants that can reject
     valid inputs.

 Thus, to avoid rejecting valid test cases (including the samples),
 and since we don't have a correct, proven reachability criterion,
 the validator will:
   - Enforce all *explicit* input-format constraints.
   - Enforce canonical numeric format rules (not applicable here since
     the input is purely a string).
   - Be whitespace-strict (exactly one line + EOF).
   - NOT attempt additional semantic reachability checks that are not
     rigorously implied and known to be correct.

 This complies with the instructions:
   - Do not assume rules from other problems.
   - Do not introduce incorrect "global" checks that contradict samples.
*/

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single token X: only letters K, S, A, length 1..5e5.
    // Using regex for allowed characters; we will additionally check length.
    string X = inf.readToken("[KSA]+", "X");
    inf.readEoln();

    int n = (int)X.size();
    ensuref(1 <= n && n <= 500000,
            "Length |X| must be in [1, 5*10^5], got %d", n);

    // Extra safety: all characters must be exactly 'K', 'S', or 'A'.
    // (The regex already enforces this, but we keep a clear explicit check.)
    for (int i = 0; i < n; ++i) {
        char c = X[i];
        ensuref(c == 'K' || c == 'S' || c == 'A',
                "Invalid character '%c' at position %d (must be K, S, or A)",
                c, i + 1);
    }

    inf.readEof();
}
