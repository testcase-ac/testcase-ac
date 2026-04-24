#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    const int maxDocLen = 20;
    const int maxPatternLen = 10;
    int n = rnd.next(1, maxDocLen);
    int m = rnd.next(1, min(n, maxPatternLen));

    // Prepare a small alphabet
    string alph = "abcdefghijklmnopqrstuvwxyz";
    shuffle(alph.begin(), alph.end());
    int letterCnt = rnd.next(1, min(3, 26));
    vector<char> letters(alph.begin(), alph.begin() + letterCnt);

    // Space probability
    double spaceProb = rnd.next(0.0, 1.0);

    // Build random document
    string doc;
    doc.reserve(n);
    for (int i = 0; i < n; i++) {
        if (rnd.next() < spaceProb) {
            doc.push_back(' ');
        } else {
            doc.push_back(rnd.any(letters));
        }
    }
    // Ensure at least one non-space in document
    bool hasLetter = false;
    for (char c : doc) if (c != ' ') { hasLetter = true; break; }
    if (!hasLetter) {
        int pos = rnd.next(0, n - 1);
        doc[pos] = rnd.any(letters);
    }

    // Build random pattern
    bool forceOverlapFriendly = (rnd.next() < 0.3);
    string pattern;
    pattern.reserve(m);
    if (forceOverlapFriendly) {
        // Repeated same character
        char c = rnd.any(letters);
        for (int i = 0; i < m; i++) pattern.push_back(c);
    } else {
        // General pattern with spaces
        for (int i = 0; i < m; i++) {
            if (rnd.next() < spaceProb) pattern.push_back(' ');
            else pattern.push_back(rnd.any(letters));
        }
    }
    // Ensure at least one non-space in pattern
    hasLetter = false;
    for (char c : pattern) if (c != ' ') { hasLetter = true; break; }
    if (!hasLetter) {
        int pos = rnd.next(0, m - 1);
        pattern[pos] = rnd.any(letters);
    }

    // Force some occurrences of the pattern into the document
    int maxForced = n / m;
    int k = (maxForced > 0 ? rnd.next(0, min(maxForced, 3)) : 0);
    for (int i = 0; i < k; i++) {
        int pos = rnd.next(0, n - m);
        for (int j = 0; j < m; j++) {
            doc[pos + j] = pattern[j];
        }
    }

    // Output
    printf("%s\n", doc.c_str());
    printf("%s\n", pattern.c_str());

    return 0;
}
