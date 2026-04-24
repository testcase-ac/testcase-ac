#include "testlib.h"
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int lenA = rnd.next(1, 10);
    int lenB = rnd.next(1, 10);
    double pMulti = rnd.next();  // chance to have multiple common letters

    int maxCommon = min(lenA, lenB);
    int k;
    if (pMulti < 0.5 || maxCommon == 1) {
        k = 1;
    } else {
        k = rnd.next(2, maxCommon);
    }

    // Choose k distinct common letters
    vector<char> alphabet(26);
    iota(alphabet.begin(), alphabet.end(), 'A');
    shuffle(alphabet.begin(), alphabet.end());
    vector<char> common(alphabet.begin(), alphabet.begin() + k);

    // Assign positions for common letters in A and B
    vector<int> posA(lenA), posB(lenB);
    iota(posA.begin(), posA.end(), 0);
    iota(posB.begin(), posB.end(), 0);
    shuffle(posA.begin(), posA.end());
    shuffle(posB.begin(), posB.end());
    posA.resize(k);
    posB.resize(k);

    // Build strings
    string A(lenA, '?'), B(lenB, '?');
    for (int i = 0; i < k; ++i) {
        A[posA[i]] = common[i];
        B[posB[i]] = common[i];
    }
    string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < lenA; ++i) {
        if (A[i] == '?')
            A[i] = rnd.any(alph);
    }
    for (int i = 0; i < lenB; ++i) {
        if (B[i] == '?')
            B[i] = rnd.any(alph);
    }

    // Output one test case: two words on one line
    println(A, B);
    return 0;
}
