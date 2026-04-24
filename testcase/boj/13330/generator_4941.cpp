#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    bool wantPossible = rnd.next(0, 4) != 0; // ~80% chance to generate possible case
    int n;
    int k, l;
    string w;

    // Sample theta parameters
    l = rnd.next(1, 10);
    k = rnd.next(1, l);

    if (wantPossible) {
        // Generate a concatenation of few theta-palindromes
        int pieces;
        int r = rnd.next(1, 100);
        if (r <= 50) pieces = 1;
        else if (r <= 80) pieces = 2;
        else pieces = 3;

        w = "";
        for (int pi = 0; pi < pieces; pi++) {
            // find uLen that allows some vLen >= 0
            int uLen = 1, vLen = 0;
            bool found = false;
            for (int it = 0; it < 10; it++) {
                int candU = rnd.next(1, 3);
                // floorBound = floor((2*uLen*l)/k) - 2*uLen
                int bound = (2 * candU * l) / k - 2 * candU;
                if (bound >= 0) {
                    uLen = candU;
                    vLen = rnd.next(0, min(bound, 3));
                    found = true;
                    break;
                }
            }
            if (!found) {
                // fallback to maximal ratio uLen=1,vLen=0 always valid since k<=l
                uLen = 1; vLen = 0;
            }
            // build u of random letters a-c
            string u;
            for (int i = 0; i < uLen; i++)
                u.push_back(char('a' + rnd.next(0, 2)));
            // build v of random letters d-f
            string v;
            for (int i = 0; i < vLen; i++)
                v.push_back(char('d' + rnd.next(0, 2)));
            string urev = u;
            reverse(urev.begin(), urev.end());
            w += u + v + urev;
        }
        n = w.size();
    } else {
        // Generate random string probably impossible
        n = rnd.next(1, 15);
        w = "";
        for (int i = 0; i < n; i++)
            w.push_back(char('a' + rnd.next(0, 25)));
    }

    // Output
    println(n, k, l);
    println(w);

    return 0;
}
