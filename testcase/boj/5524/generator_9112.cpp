#include "testlib.h"
using namespace std;

string toUpperStr(string s) {
    for (char &c : s) {
        if (c >= 'a' && c <= 'z') c = char(c - 'a' + 'A');
    }
    return s;
}

string toLowerStr(string s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') c = char(c - 'A' + 'a');
    }
    return s;
}

string altCaseStr(string s, bool startUpper) {
    bool upper = startUpper;
    for (char &c : s) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            if (upper) {
                if (c >= 'a' && c <= 'z') c = char(c - 'a' + 'A');
            } else {
                if (c >= 'A' && c <= 'Z') c = char(c - 'A' + 'a');
            }
            upper = !upper;
        }
    }
    return s;
}

string randomLetters(int len, int mode) {
    // mode: 0 = any case per char, 1 = all upper, 2 = all lower
    string s(len, 'a');
    for (int i = 0; i < len; ++i) {
        if (mode == 1) {
            s[i] = char('A' + rnd.next(0, 25));
        } else if (mode == 2) {
            s[i] = char('a' + rnd.next(0, 25));
        } else {
            // random letter then random case
            char base = char('a' + rnd.next(0, 25));
            if (rnd.next(0, 1) == 0)
                s[i] = base;
            else
                s[i] = char(base - 'a' + 'A');
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a scenario type to get diverse patterns
    int scenario = rnd.next(1, 6);
    int N = 0;
    vector<string> names;

    // Some handy base names (within length 1..20)
    vector<string> baseNames = {
        "A", "B", "JOI", "joi", "Test", "alpha", "BETA", "xyz",
        "XYZ", "MiXeD", "Case", "a", "z", "AZ", "za", "YamaMoto",
        "SUZUKI", "tanaka", "tAkAhAshi", "Ito"
    };

    if (scenario == 1) {
        // All uppercase, some random, some from base
        N = rnd.wnext(20, 2) + 1; // bias towards larger N but <= 21
        if (N > 20) N = 20;
        for (int i = 0; i < N; ++i) {
            string s;
            if (rnd.next(0, 3) == 0) {
                s = toUpperStr(rnd.any(baseNames));
            } else {
                int len = rnd.next(1, 20);
                s = randomLetters(len, 1); // all upper
            }
            names.push_back(s);
        }
    } else if (scenario == 2) {
        // All lowercase
        N = rnd.wnext(15, -2) + 1; // bias towards smaller N
        if (N > 20) N = 20;
        for (int i = 0; i < N; ++i) {
            string s;
            if (rnd.next(0, 3) == 0) {
                s = toLowerStr(rnd.any(baseNames));
            } else {
                int len = rnd.next(1, 20);
                s = randomLetters(len, 2); // all lower
            }
            names.push_back(s);
        }
    } else if (scenario == 3) {
        // Fully random mixed case per character
        N = rnd.next(5, 20);
        for (int i = 0; i < N; ++i) {
            int len = rnd.next(1, 20);
            names.push_back(randomLetters(len, 0));
        }
    } else if (scenario == 4) {
        // Alternating case pattern based on base names
        N = rnd.next(5, 15);
        for (int i = 0; i < N; ++i) {
            string base = rnd.any(baseNames);
            bool startUpper = (i % 2 == 0);
            names.push_back(altCaseStr(base, startUpper));
        }
    } else if (scenario == 5) {
        // Many duplicates with varying cases
        N = rnd.next(8, 20);
        int K = rnd.next(1, min(5, N)); // number of distinct logical names
        vector<string> baseSet;
        for (int i = 0; i < K; ++i)
            baseSet.push_back(rnd.any(baseNames));
        for (int i = 0; i < N; ++i) {
            string b = rnd.any(baseSet);
            int caseType = rnd.next(0, 2);
            if (caseType == 0) b = toLowerStr(b);
            else if (caseType == 1) b = toUpperStr(b);
            else b = altCaseStr(b, rnd.next(0, 1));
            names.push_back(b);
        }
        shuffle(names.begin(), names.end());
    } else if (scenario == 6) {
        // Edge lengths: ensure length 1 and 20, mix cases
        N = rnd.next(5, 15);
        // First ensure length 1
        char c1 = (rnd.next(0, 1) == 0) ? char('A' + rnd.next(0, 25))
                                        : char('a' + rnd.next(0, 25));
        names.push_back(string(1, c1));
        // Ensure length 20
        names.push_back(randomLetters(20, rnd.next(0, 2)));
        // Remaining
        for (int i = 2; i < N; ++i) {
            int len;
            if (i == 2) len = rnd.next(2, 5);
            else if (i == 3) len = rnd.next(15, 20);
            else len = rnd.next(1, 20);
            int mode = rnd.next(0, 2);
            names.push_back(randomLetters(len, mode));
        }
        shuffle(names.begin(), names.end());
    }

    // Output
    println(N);
    for (const string &s : names) {
        println(s);
    }

    return 0;
}
