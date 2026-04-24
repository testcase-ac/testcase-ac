/* generator code */
#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose lengths: A shorter, B longer
    int La = rnd.next(1, 8);
    int extra = rnd.next(0, 8);
    int Lb = La + extra;

    // Choose alphabet size
    int K = rnd.next(2, 26);
    vector<char> alph;
    for (int i = 0; i < K; i++) alph.push_back(char('a' + i));

    // Build B randomly
    string B;
    B.reserve(Lb);
    for (int i = 0; i < Lb; i++) {
        B.push_back(rnd.any(alph));
    }

    // Choose a segment in B to derive A
    int off = rnd.next(0, Lb - La);

    // Copy segment
    string A = B.substr(off, La);

    // Introduce some mismatches into A
    int mismatches = rnd.next(0, La);
    vector<int> pos(La);
    for (int i = 0; i < La; i++) pos[i] = i;
    shuffle(pos.begin(), pos.end());
    for (int i = 0; i < mismatches; i++) {
        int p = pos[i];
        char orig = A[p];
        char c;
        do {
            c = rnd.any(alph);
        } while (c == orig);
        A[p] = c;
    }

    // Output single test case: A and B
    println(A, B);

    return 0;
}
