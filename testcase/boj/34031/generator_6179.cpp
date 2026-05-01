#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

string genRandom(int l) {
    string s;
    s.reserve(l);
    for (int i = 0; i < l; i++) {
        s.push_back(rnd.next(0,1) ? ')' : '(');
    }
    return s;
}

string genDyck(int pairs) {
    string s;
    s.reserve(2 * pairs);
    int open = pairs, close = pairs;
    while (open + close > 0) {
        if (open > 0 && close > 0) {
            if (rnd.next(0,1))
                { s.push_back('('); open--; }
            else
                { s.push_back(')'); close--; }
        } else if (open > 0) {
            s.push_back('(');
            open--;
        } else {
            s.push_back(')');
            close--;
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose lengths for A and B with variability
    int bucketA = rnd.next(0, 2);
    int lA;
    if (bucketA == 0) lA = rnd.next(1, 5);
    else if (bucketA == 1) lA = rnd.next(6, 15);
    else lA = rnd.next(16, 30);

    int bucketB = rnd.next(0, 2);
    int lB;
    if (bucketB == 0) lB = rnd.next(1, 5);
    else if (bucketB == 1) lB = rnd.next(6, 15);
    else lB = rnd.next(16, 30);

    int method = rnd.next(0, 2);
    string A, B;
    if (method == 0) {
        // both completely random
        A = genRandom(lA);
        B = genRandom(lB);
    } else if (method == 1) {
        // A has a valid Dyck prefix, then random tail; B random
        int maxPairsA = lA / 2;
        int p = maxPairsA > 0 ? rnd.next(1, maxPairsA) : 0;
        string dy = genDyck(p);
        int rem = lA - 2 * p;
        A = dy + genRandom(rem);
        B = genRandom(lB);
    } else {
        // B has a valid Dyck prefix, then random tail; A random
        int maxPairsB = lB / 2;
        int p = maxPairsB > 0 ? rnd.next(1, maxPairsB) : 0;
        string dy = genDyck(p);
        int rem = lB - 2 * p;
        B = dy + genRandom(rem);
        A = genRandom(lA);
    }

    // Output the two strings
    printf("%s\n", A.c_str());
    printf("%s\n", B.c_str());
    return 0;
}
