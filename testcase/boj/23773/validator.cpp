#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and w
    int n = inf.readInt(1, 5000, "n");
    inf.readSpace();
    int w = inf.readInt(1, 5000, "w");
    inf.readEoln();

    vector<string> names;
    names.reserve(n);
    long long totalLen = 0;
    string prev = "";

    for (int i = 0; i < n; i++) {
        // Each filename: lowercase letters only, length between 1 and w
        string s = inf.readToken("[a-z]+", "filename");
        inf.readEoln();

        // Check length bounds
        ensuref((int)s.size() >= 1,
                "Filename %d is empty", i+1);
        ensuref((int)s.size() <= w,
                "Filename %d ('%s') length %d exceeds w=%d",
                i+1, s.c_str(), (int)s.size(), w);

        // Accumulate total length
        totalLen += (int)s.size();
        ensuref(totalLen <= 1000000LL,
                "Total length of filenames exceeds 1e6 after reading filename %d", i+1);

        // Check lexicographic order and distinctness
        if (i > 0) {
            ensuref(s > prev,
                    "Filename %d ('%s') is not strictly greater than previous filename ('%s')",
                    i+1, s.c_str(), prev.c_str());
        }
        prev = s;

        names.push_back(s);
    }

    // End of file
    inf.readEof();
    return 0;
}
