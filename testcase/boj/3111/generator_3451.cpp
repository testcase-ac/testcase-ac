#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: base alphabet size
    int K = rnd.next(1, 5); // use letters 'a'..'a'+K-1
    // Text length
    int nT = rnd.next(1, 20);

    // Pattern length up to 6 (can exceed nT)
    int maxPat = 6;
    int L = rnd.next(1, maxPat);

    // Generate pattern A
    string A;
    if (rnd.next() < 0.3) {
        // repeating single char
        char c = char('a' + rnd.next(K));
        A = string(L, c);
    } else {
        for (int i = 0; i < L; i++) {
            A.push_back(char('a' + rnd.next(K)));
        }
    }

    // Generate base text T
    string T;
    T.reserve(nT);
    for (int i = 0; i < nT; i++) {
        T.push_back(char('a' + rnd.next(K)));
    }

    // Insert a few explicit copies of A to ensure pattern occurrences
    int insertTimes = rnd.next(0, 2);
    for (int it = 0; it < insertTimes; it++) {
        int pos = rnd.next(0, (int)T.size());
        T.insert(pos, A);
        if ((int)T.size() > 20) break;
    }

    // Output pattern A and text T
    println(A);
    println(T);
    return 0;
}
