#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for lengths
    int maxLen = 20;
    int n1 = rnd.next(1, maxLen);
    int n2 = rnd.next(1, maxLen);

    // Hyper-parameter for alphabet size
    string all = "ACGT";
    int alphaSize = rnd.next(1, 4);
    string letters = all.substr(0, alphaSize);

    // Ensure at least one common character
    char commonChar = rnd.any(letters);

    string s1(n1, ' '), s2(n2, ' ');

    // With 50% probability, insert a common substring
    if (rnd.next(0, 1) == 1 && n1 > 1 && n2 > 1) {
        int L = rnd.next(1, min(n1, n2));
        // build a random common substring
        string sub;
        for (int i = 0; i < L; i++)
            sub.push_back(rnd.any(letters));
        int p1 = rnd.next(0, n1 - L);
        int p2 = rnd.next(0, n2 - L);
        // fill and embed
        for (int i = 0; i < n1; i++) {
            if (i >= p1 && i < p1 + L) s1[i] = sub[i - p1];
            else s1[i] = rnd.any(letters);
        }
        for (int i = 0; i < n2; i++) {
            if (i >= p2 && i < p2 + L) s2[i] = sub[i - p2];
            else s2[i] = rnd.any(letters);
        }
    } else {
        // fill random and force one common char
        int pos1 = rnd.next(0, n1 - 1);
        int pos2 = rnd.next(0, n2 - 1);
        for (int i = 0; i < n1; i++)
            s1[i] = rnd.any(letters);
        for (int i = 0; i < n2; i++)
            s2[i] = rnd.any(letters);
        s1[pos1] = commonChar;
        s2[pos2] = commonChar;
    }

    // Output
    println(n1);
    println(s1);
    println(n2);
    println(s2);

    return 0;
}
