#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Alphabet of uppercase letters
    const string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Random lengths for the two strings
    int lenA = rnd.next(1, 10);
    int lenB = rnd.next(1, 10);

    // With some probability, inject a common substring
    if (rnd.next() < 0.7) {
        int Lmax = min(lenA, lenB);
        // Choose a skew parameter for diversity in common length
        vector<int> skew = { -2, -1, 1, 2 };
        int t = rnd.any(skew);
        // rnd.wnext generates [0, Lmax-1], so +1 gives [1, Lmax]
        int commonLen = rnd.wnext(Lmax, t) + 1;

        // Build the common substring
        string common;
        for (int i = 0; i < commonLen; i++) {
            common.push_back(rnd.any(ALPHA));
        }

        // Initialize A and B with random letters
        string A(lenA, ' '), B(lenB, ' ');
        for (int i = 0; i < lenA; i++) A[i] = rnd.any(ALPHA);
        for (int i = 0; i < lenB; i++) B[i] = rnd.any(ALPHA);

        // Place the common substring at random positions
        int posA = rnd.next(0, lenA - commonLen);
        int posB = rnd.next(0, lenB - commonLen);
        for (int i = 0; i < commonLen; i++) {
            A[posA + i] = common[i];
            B[posB + i] = common[i];
        }

        // Output the two strings
        println(A);
        println(B);
    }
    else {
        // Fully random strings (no guaranteed common substring)
        string A(lenA, ' '), B(lenB, ' ');
        for (int i = 0; i < lenA; i++) A[i] = rnd.any(ALPHA);
        for (int i = 0; i < lenB; i++) B[i] = rnd.any(ALPHA);
        println(A);
        println(B);
    }

    return 0;
}
