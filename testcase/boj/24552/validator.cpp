#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[()]{3,100000}", "S");
    inf.readEoln();
    inf.readEof();

    int n = (int)s.size();
    ensuref(n % 2 == 1, "|S| must be odd: %d", n);

    vector<int> pref(n + 1, 0);
    vector<int> minPrefBefore(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + (s[i] == '(' ? 1 : -1);
        minPrefBefore[i + 1] = min(minPrefBefore[i], pref[i + 1]);
    }

    vector<int> minPrefFrom(n + 1, pref[n]);
    for (int i = n - 1; i >= 0; --i) {
        minPrefFrom[i] = min(pref[i + 1], minPrefFrom[i + 1]);
    }

    bool hasValidDeletion = false;
    for (int i = 0; i < n; ++i) {
        if (minPrefBefore[i] < 0) {
            continue;
        }
        if (s[i] == '(' && pref[n] == 1 && minPrefFrom[i] >= 1) {
            hasValidDeletion = true;
        }
        if (s[i] == ')' && pref[n] == -1 && minPrefFrom[i] >= -1) {
            hasValidDeletion = true;
        }
    }

    ensuref(hasValidDeletion, "no character can be removed to make a valid bracket sequence");
}
