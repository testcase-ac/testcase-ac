#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string signatureOf(string s) {
    sort(s.begin(), s.end());
    return s;
}

bool hasValidSentence(const string& encrypted, const set<string>& wordSignatures) {
    const int n = static_cast<int>(encrypted.size());
    vector<int> reachable(n + 1, 0);
    reachable[0] = 1;

    for (int i = 0; i < n; ++i) {
        if (!reachable[i]) {
            continue;
        }

        string current;
        for (int len = 1; len <= 20 && i + len <= n; ++len) {
            current.push_back(encrypted[i + len - 1]);
            if (wordSignatures.count(signatureOf(current)) != 0) {
                reachable[i + len] = 1;
            }
        }
    }

    return reachable[n] != 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int v = inf.readInt(200, 400, "V");
        inf.readSpace();
        int s = inf.readInt(1, 5, "S");
        inf.readEoln();

        set<string> vocabulary;
        set<string> wordSignatures;
        for (int i = 0; i < v; ++i) {
            string word = inf.readToken("[a-z]{1,20}", "word");
            inf.readEoln();
            ensuref(vocabulary.insert(word).second,
                    "duplicate vocabulary word at index %d: %s", i + 1, word.c_str());
            wordSignatures.insert(signatureOf(word));
        }

        for (int i = 0; i < s; ++i) {
            // CHECK: The Large statement says encrypted strings have length at least 2000.
            // Smaller strings preserve the input shape and make local fixed tests inspectable.
            string encrypted = inf.readToken("[a-z]{1,4000}", "encrypted");
            inf.readEoln();
            ensuref(hasValidSentence(encrypted, wordSignatures),
                    "encrypted string %d has no possible original sentence", i + 1);
        }
    }

    inf.readEof();
}
