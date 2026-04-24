#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: probability of generating a valid bracket string
    double valid_prob = rnd.next(0.0, 1.0);

    // Function to generate a valid bracket sequence with exactly `pairs` pairs
    auto genValid = [&](int pairs) {
        string s;
        vector<char> stk;
        int opensRem = pairs;
        while (opensRem > 0 || !stk.empty()) {
            // decide whether to open a new bracket or close one
            if (opensRem > 0 && (stk.empty() ||
                rnd.next(0.0, 1.0) < double(opensRem) / (opensRem + (int)stk.size()))) {
                // open
                char o = rnd.next(0, 1) == 0 ? '(' : '[';
                s.push_back(o);
                stk.push_back(o);
                opensRem--;
            } else {
                // close
                char o = stk.back(); stk.pop_back();
                s.push_back(o == '(' ? ')' : ']');
            }
        }
        return s;
    };

    string result;
    if (rnd.next() < valid_prob) {
        // Generate a valid sequence
        // At most 15 pairs so length <= 30
        int pairs = rnd.next(1, 15);
        result = genValid(pairs);
    } else {
        // Generate an invalid sequence by taking a valid one and appending a mismatched bracket
        // Use at most 14 pairs so base length <= 28, appended one bracket => <=29
        int pairs = rnd.next(1, 14);
        result = genValid(pairs);
        // append an extra closing bracket to break validity
        char extra = rnd.next(0, 1) == 0 ? ')' : ']';
        result.push_back(extra);
    }

    // Output the single test case
    println(result);
    return 0;
}
