#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

static string signatureOf(string s) {
    sort(s.begin(), s.end());
    return s;
}

static bool canDecode(const vector<string>& wordSignatures, const string& cipher) {
    const int n = static_cast<int>(cipher.size());
    vector<int> reachable(n + 1, 0);
    reachable[0] = 1;

    for (int i = 0; i < n; ++i) {
        if (!reachable[i]) {
            continue;
        }
        for (const string& word : wordSignatures) {
            const int len = static_cast<int>(word.size());
            if (i + len > n) {
                continue;
            }
            string part = cipher.substr(i, len);
            if (signatureOf(part) == word) {
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

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int v = inf.readInt(5, 10, "V");
        inf.readSpace();
        int s = inf.readInt(1, 5, "S");
        inf.readEoln();

        set<string> vocabulary;
        vector<string> wordSignatures;
        for (int i = 0; i < v; ++i) {
            string word = inf.readToken("[a-z]{1,5}", "word");
            inf.readEoln();
            ensuref(vocabulary.insert(word).second,
                    "duplicate vocabulary word in case %d: %s", tc, word.c_str());
            wordSignatures.push_back(signatureOf(word));
        }

        for (int i = 0; i < s; ++i) {
            string cipher = inf.readToken("[a-z]{1,50}", "cipher");
            inf.readEoln();
            ensuref(canDecode(wordSignatures, cipher),
                    "cipher %d in case %d has no valid original sentence: %s",
                    i + 1, tc, cipher.c_str());
        }
    }

    inf.readEof();
}
