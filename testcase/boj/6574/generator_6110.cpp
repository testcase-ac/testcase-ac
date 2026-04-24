#include "testlib.h"
#include <string>
using namespace std;

string genRand(int len, char lo='a', char hi='z') {
    string s;
    int base = lo, range = hi - lo + 1;
    for (int i = 0; i < len; i++)
        s.push_back(char(base + rnd.next(range - 1)));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(3, 6);
    for (int i = 0; i < T; i++) {
        int tp = rnd.next(1, 7);
        string A, B;
        if (tp == 1) {
            // identical
            int L = rnd.next(1, 10);
            A = genRand(L);
            B = A;
        } else if (tp == 2) {
            // one contains the other
            bool flip = rnd.next(0,1);
            int L = rnd.next(3, 12);
            string X = genRand(L);
            int lenSub = rnd.next(1, L);
            int st = rnd.next(0, L - lenSub);
            string Y = X.substr(st, lenSub);
            if (!flip) {
                A = X; B = Y;
            } else {
                A = Y; B = X;
            }
        } else if (tp == 3) {
            // no overlap possible (disjoint alphabets)
            int la = rnd.next(1, 12), lb = rnd.next(1, 12);
            A = genRand(la, 'a', 'e');
            B = genRand(lb, 'f', 'j');
        } else if (tp == 4) {
            // suffix A overlaps prefix B
            int k = rnd.next(1, 6);
            string O = genRand(k);
            int u = rnd.next(0, 5), v = rnd.next(0, 5);
            string U = genRand(u);
            string V = genRand(v);
            A = U + O;
            B = O + V;
        } else if (tp == 5) {
            // suffix B overlaps prefix A
            int k = rnd.next(1, 6);
            string O = genRand(k);
            int u = rnd.next(0, 5), v = rnd.next(0, 5);
            string U = genRand(u);
            string V = genRand(v);
            B = U + O;
            A = O + V;
        } else if (tp == 6) {
            // repeated pattern
            int p = rnd.next(1, 5);
            string P = genRand(p);
            int r1 = rnd.next(2, 4), r2 = rnd.next(2, 4);
            A.clear(); B.clear();
            for (int j = 0; j < r1; j++) A += P;
            for (int j = 0; j < r2; j++) B += P;
        } else {
            // random
            int la = rnd.next(1, 15), lb = rnd.next(1, 15);
            A = genRand(la);
            B = genRand(lb);
        }
        // ensure non-empty
        if (A.empty()) A = "a";
        if (B.empty()) B = "b";
        println(A, B);
    }
    return 0;
}
