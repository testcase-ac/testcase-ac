#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Random lengths with bias: sometimes small, sometimes large
    int n = rnd.wnext(30, rnd.next(-3, 3)) + 1;
    int m = rnd.wnext(30, rnd.next(-3, 3)) + 1;

    // Choose a pattern type for diversity
    int tp = rnd.next(0, 5);
    string s, t;

    switch (tp) {
        case 0:
            // Fully random bits
            for (int i = 0; i < n; i++) s += char('0' + rnd.next(0, 1));
            for (int i = 0; i < m; i++) t += char('0' + rnd.next(0, 1));
            break;
        case 1:
            // Alternating patterns, offset by 1
            for (int i = 0; i < n; i++) s += char('0' + (i % 2 == 0 ? 0 : 1));
            for (int i = 0; i < m; i++) t += char('0' + (i % 2 == 0 ? 1 : 0));
            break;
        case 2:
            // s = all zeros, t = random
            s = string(n, '0');
            for (int i = 0; i < m; i++) t += char('0' + rnd.next(0, 1));
            break;
        case 3:
            // s = all ones, t = random
            s = string(n, '1');
            for (int i = 0; i < m; i++) t += char('0' + rnd.next(0, 1));
            break;
        case 4: {
            // Both share a same base, but truncated differently
            int L = max(n, m);
            string base;
            for (int i = 0; i < L; i++) base += char('0' + rnd.next(0, 1));
            s = base.substr(0, n);
            t = base.substr(0, m);
            break;
        }
        case 5: {
            // Random runs of length 1 to 3
            auto genRuns = [&](int len) {
                string r;
                int i = 0;
                while (i < len) {
                    int block = rnd.next(1, 3);
                    char c = char('0' + rnd.next(0, 1));
                    for (int k = 0; k < block && i < len; k++, i++)
                        r += c;
                }
                return r;
            };
            s = genRuns(n);
            t = genRuns(m);
            break;
        }
    }

    // Output two binary strings
    println(s);
    println(t);

    return 0;
}
