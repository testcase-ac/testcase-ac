#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for length n in [1..25] with bias
    double t = rnd.next();
    int n;
    if (t < 0.1) n = 1;
    else if (t < 0.2) n = 2;
    else if (t < 0.4) n = rnd.next(3, 5);
    else if (t < 0.7) n = rnd.next(6, 15);
    else n = rnd.next(16, 25);

    // Sum s must satisfy 1 ≤ s ≤ 25*n
    int maxS = 25 * n;
    double u = rnd.next();
    int s;
    if (u < 0.2) {
        // small s
        s = rnd.next(1, min(25, maxS));
    } else if (u < 0.4) {
        // large s
        s = rnd.next(maxS / 2, maxS);
    } else if (u < 0.6) {
        // medium-low s
        s = rnd.next(n, min(n * 5, maxS));
    } else {
        // full range
        s = rnd.next(1, maxS);
    }

    // Alphabet limit: use letters in ['a'..'a'+maxChar]
    int maxChar = rnd.next(0, 25);

    // Choose pattern type for variability
    int vType = rnd.next(0, 3);
    string str(n, 'a');
    if (vType == 0) {
        // fully random
        for (int i = 0; i < n; i++)
            str[i] = char('a' + rnd.next(0, maxChar));
    } else if (vType == 1) {
        // all same letter
        char c = char('a' + rnd.next(0, maxChar));
        for (int i = 0; i < n; i++)
            str[i] = c;
    } else if (vType == 2) {
        // increasing sequence cyclic over alphabet
        for (int i = 0; i < n; i++)
            str[i] = char('a' + (i % (maxChar + 1)));
    } else {
        // repeat a small random pattern of length up to 5
        int p = rnd.next(1, min(n, 5));
        string pat(p, 'a');
        for (int i = 0; i < p; i++)
            pat[i] = char('a' + rnd.next(0, maxChar));
        for (int i = 0; i < n; i++)
            str[i] = pat[i % p];
    }

    // Output the generated test case
    println(s);
    println(str);

    return 0;
}
