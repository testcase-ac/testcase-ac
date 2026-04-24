#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();

        // Read first public key
        vector<string> key1(n);
        set<string> uniq1;
        for (int i = 0; i < n; i++) {
            key1[i] = inf.readToken("[A-Z]{1,10}", "key1_i");
            if (i + 1 < n)
                inf.readSpace();
            else
                inf.readEoln();
            // ensure unique in key1
            bool ins = uniq1.insert(key1[i]).second;
            ensuref(ins,
                    "Duplicate word '%s' in first public key at position %d",
                    key1[i].c_str(), i + 1);
        }

        // Read second public key
        vector<string> key2(n);
        for (int i = 0; i < n; i++) {
            key2[i] = inf.readToken("[A-Z]{1,10}", "key2_i");
            if (i + 1 < n)
                inf.readSpace();
            else
                inf.readEoln();
        }
        // Check key2 is a permutation of key1
        {
            vector<string> s1(key1.begin(), key1.end());
            vector<string> s2(key2.begin(), key2.end());
            sort(s1.begin(), s1.end());
            sort(s2.begin(), s2.end());
            ensuref(s1 == s2,
                    "Second public key is not a permutation of the first public key");
        }

        // Read ciphertext
        for (int i = 0; i < n; i++) {
            inf.readToken("[A-Z]{1,10}", "cipher_i");
            if (i + 1 < n)
                inf.readSpace();
            else
                inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
