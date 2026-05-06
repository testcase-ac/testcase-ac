#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Check if a string s (number, no leading zeros) is a vampire number per statement.
bool isVampire(const string &s) {
    int L = (int)s.size();
    if (L % 2 == 1) return false; // must have even digits
    int n = L / 2;

    string sortedN = s;
    sort(sortedN.begin(), sortedN.end());

    // Convert N to unsigned long long (fits in <=70 bits, but sample uses >18 digits,
    // and statement contradicts, so we only use string-based factorization where needed).
    // However, exhaustive factorization up to 10^9 is infeasible. So we must instead
    // check via combinatorial generation of digit splits: but that is exponential.
    // Observation: constraints in ICPC-style problems imply input count small and digits not huge.
    // But we must be safe. We instead loop factors around sqrt(N) with 64-bit where possible.
    // For longer than 18 digits (up to 18?), we are told "each number will have at most 18 digits"
    // in the statement we must validate, so in validator we can assume that, and factorization
    // with unsigned long long is fine.
    unsigned long long N = 0;
    for (char c : s) {
        N = N * 10 + (c - '0');
    }

    // Generate possible n-digit factors: from 10^(n-1) to 10^n - 1
    unsigned long long low = 1;
    for (int i = 1; i < n; ++i) low *= 10ULL;
    unsigned long long high = low * 10ULL - 1;

    // Enumerate factor a in [low, high]
    for (unsigned long long a = low; a <= high; ++a) {
        // check "no consecutive zeroes" for a
        {
            unsigned long long x = a;
            int prev = -1;
            bool bad = false;
            for (int i = 0; i < n; ++i) {
                int d = (int)(x % 10);
                x /= 10;
                if (d == 0 && prev == 0) { bad = true; break; }
                prev = d;
            }
            if (bad) continue;
        }

        if (N % a != 0) continue;
        unsigned long long b = N / a;
        if (b < low || b > high) continue;

        // check "no consecutive zeroes" for b
        {
            unsigned long long x = b;
            int prev = -1;
            bool bad = false;
            for (int i = 0; i < n; ++i) {
                int d = (int)(x % 10);
                x /= 10;
                if (d == 0 && prev == 0) { bad = true; break; }
                prev = d;
            }
            if (bad) continue;
        }

        // check digit multiset
        string t = to_string(a) + to_string(b);
        sort(t.begin(), t.end());
        if (t == sortedN) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input: arbitrary number of lines, each a single number (no leading zeros),
    // up to 18 digits, terminated by a single "0" line.
    // We must validate:
    //  - each line is a canonical non-negative integer without leading zeros
    //  - at most 18 decimal digits
    //  - there is at least the final "0" line
    //  - no extra whitespace
    //  - all numbers except the final zero are > 0
    //  - additionally, according to typical problem text, statement says:
    //    "each number will have at most 18 digits" AND examples include >18,
    //    but we must follow the textual constraint: enforce <= 18.
    //  - No further global properties guaranteed, so we don't require them,
    //    but the problem does NOT guarantee "answer always exists", so we
    //    do NOT need to simulate for any such thing.

    bool sawTerminator = false;
    int lineIndex = 0;

    while (true) {
        // If EOF without terminator, it's invalid
        if (inf.seekEof()) break; // testlib way; but we must afterwards ensure sawTerminator
        string token = inf.readToken("[0-9]+", "number");
        ++lineIndex;
        inf.readEoln();

        // canonical form: no leading zeros unless exactly "0"
        ensuref(token.size() == 1 || token[0] != '0',
                "Leading zero in number on line %d: '%s'",
                lineIndex, token.c_str());

        // at most 18 digits
        ensuref(token.size() <= 18,
                "Number too long on line %d: length %d > 18",
                lineIndex, (int)token.size());

        if (token == "0") {
            ensuref(!sawTerminator,
                    "Multiple terminator lines '0' found, first at some earlier line, again at line %d",
                    lineIndex);
            sawTerminator = true;
            break; // must end of input after this
        } else {
            // positive integer
            // Additionally, from validator perspective we can check that
            // the number being declared in the input makes sense with the
            // promise "at most 18 digits": already enforced.
            // There is no guarantee that it must be or must not be a vampire number;
            // that's task of solution. BUT the description includes phrase
            // "Write a program that reads in a series of numbers (each at most 18 digits)
            //  and prints whether or not that number is a Vampire number."
            // No extra global properties to enforce.
        }
    }

    ensuref(sawTerminator, "Input must end with a single line containing '0'");

    inf.readEof();
}
