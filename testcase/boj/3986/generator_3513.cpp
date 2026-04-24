#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

// Check if a word is good by stack-based reduction of adjacent pairs.
bool isGood(const string &s) {
    vector<char> st;
    for (char c : s) {
        if (!st.empty() && st.back() == c)
            st.pop_back();
        else
            st.push_back(c);
    }
    return st.empty();
}

// Generate a good word of even length 'len' using the grammar S->SS|aSa|bSb
string genGood(int len) {
    if (len == 0) return "";
    if (len == 2) {
        // Base pair
        return string(2, rnd.any(string("AB")));
    }
    // Decide nesting vs concatenation
    if (rnd.next() < 0.5) {
        // Nesting: x + gen(len-2) + x
        char x = rnd.any(string("AB"));
        return string(1, x) + genGood(len - 2) + string(1, x);
    } else {
        // Concatenation: split into two even parts >=2
        int half = (len - 2) / 2; // at least 1
        int parts = rnd.next(1, half);
        int len1 = parts * 2;
        int len2 = len - len1;
        return genGood(len1) + genGood(len2);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of words
    int N = rnd.next(1, 10);
    // Probability to generate a good word
    double p_good = rnd.next();
    // Probability that a bad word has even length (else odd)
    double p_bad_even = rnd.next();

    println(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < p_good) {
            // Generate a good word
            int pairs = rnd.next(1, 10);
            int len = pairs * 2;
            string s = genGood(len);
            println(s);
        } else {
            // Generate a bad word
            string s;
            if (rnd.next() < p_bad_even) {
                // Even length but not good
                int len = rnd.next(1, 10) * 2;
                // retry until it's bad
                do {
                    s.clear();
                    double pA = rnd.next();
                    for (int j = 0; j < len; j++)
                        s.push_back(rnd.next() < pA ? 'A' : 'B');
                } while (isGood(s));
            } else {
                // Odd length => always bad
                int len = rnd.next(1, 9) * 2 + 1; // 3..19
                s.clear();
                double pA = rnd.next();
                for (int j = 0; j < len; j++)
                    s.push_back(rnd.next() < pA ? 'A' : 'B');
            }
            println(s);
        }
    }
    return 0;
}
