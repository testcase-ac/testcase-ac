#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose lengths with different regimes
    int regime = rnd.next(0, 2);
    int lenA, lenB;
    if (regime == 0) {
        lenA = rnd.next(1, 10);
        lenB = rnd.next(1, 10);
    } else if (regime == 1) {
        lenA = rnd.next(10, 30);
        lenB = rnd.next(10, 30);
    } else {
        lenA = rnd.next(1, 50);
        lenB = rnd.next(1, 50);
    }
    // Choose alphabet size
    int r2 = rnd.next(0, 2);
    int alphSize;
    if (r2 == 0) alphSize = 1;
    else if (r2 == 1) alphSize = rnd.next(2, 4);
    else alphSize = rnd.next(5, 26);
    string letters;
    for (int i = 0; i < alphSize; i++) letters.push_back(char('a' + i));
    // Determine length of a common substring to embed
    int maxCommon = min(lenA, lenB);
    int Lcommon = 0;
    if (maxCommon > 0) {
        int cr = rnd.next(0, 2);
        if (cr == 0) {
            Lcommon = rnd.next(0, min(3, maxCommon));
        } else if (cr == 1) {
            Lcommon = rnd.next(maxCommon / 2, maxCommon);
        } else {
            Lcommon = rnd.next(0, maxCommon);
        }
    }
    // Build the common substring
    vector<char> T(Lcommon);
    for (int i = 0; i < Lcommon; i++) {
        T[i] = rnd.any(letters);
    }
    // Build string A
    vector<char> A(lenA);
    for (int i = 0; i < lenA; i++) {
        A[i] = rnd.any(letters);
    }
    if (Lcommon > 0) {
        int posA = rnd.next(0, lenA - Lcommon);
        for (int i = 0; i < Lcommon; i++) {
            A[posA + i] = T[i];
        }
    }
    // Build string B
    vector<char> B(lenB);
    for (int i = 0; i < lenB; i++) {
        B[i] = rnd.any(letters);
    }
    if (Lcommon > 0) {
        int posB = rnd.next(0, lenB - Lcommon);
        for (int i = 0; i < Lcommon; i++) {
            B[posB + i] = T[i];
        }
    }
    // Output the two strings
    string sA(A.begin(), A.end());
    string sB(B.begin(), B.end());
    printf("%s\n%s\n", sA.c_str(), sB.c_str());
    return 0;
}
