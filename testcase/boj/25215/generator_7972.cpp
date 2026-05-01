#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose length with bias: small, medium, or large
    double p = rnd.next();
    int n;
    if (p < 0.15) n = rnd.next(1, 5);
    else if (p < 0.85) n = rnd.next(6, 15);
    else n = rnd.next(16, 30);

    // Pattern types:
    // 0: all lowercase
    // 1: all uppercase
    // 2: alternating case, random letters
    // 3: random case, random letters
    // 4: alternating case, same letter
    int pattern = rnd.next(0, 4);
    int startCase = rnd.next(0, 1);

    string s;
    s.reserve(n);

    char sameBase = 'a' + rnd.next(0, 25);
    for (int i = 0; i < n; i++) {
        char base;
        if (pattern == 4) {
            base = sameBase;
        } else {
            base = 'a' + rnd.next(0, 25);
        }
        bool uppercase = false;
        if (pattern == 1) {
            uppercase = true;
        } else if (pattern == 2) {
            uppercase = ((i % 2) == 0 ? startCase : 1 - startCase);
        } else if (pattern == 3) {
            uppercase = rnd.next(0, 1);
        } else if (pattern == 4) {
            uppercase = ((i % 2) == 0 ? startCase : 1 - startCase);
        }
        char out = uppercase ? char('A' + (base - 'a')) : base;
        s.push_back(out);
    }

    println(s);
    return 0;
}
