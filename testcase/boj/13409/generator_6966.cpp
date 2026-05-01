#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose overall size regime
    int regime = rnd.next(1, 4);
    int n, maxlen;
    if (regime == 1) {
        n = rnd.next(1, 3);
        maxlen = rnd.next(1, 5);
    } else if (regime == 2) {
        n = rnd.next(4, 8);
        maxlen = rnd.next(5, 15);
    } else if (regime == 3) {
        n = rnd.next(6, 12);
        maxlen = rnd.next(10, 30);
    } else {
        n = rnd.next(1, 12);
        maxlen = rnd.next(1, 40);
    }
    println(n);
    for (int i = 0; i < n; i++) {
        // pick a pattern type for this pile
        int type = rnd.next(0, 3);
        // length with slight bias: use wnext for variation
        int bias = rnd.next(-1, 1);
        int len = rnd.wnext(maxlen, bias) + 1;
        string s;
        s.reserve(len);
        if (type == 0) {
            // fully random
            for (int j = 0; j < len; j++)
                s.push_back(rnd.next(0, 1) ? 'B' : 'W');
        } else if (type == 1) {
            // all B or all W
            char c = rnd.next(0, 1) ? 'B' : 'W';
            s.assign(len, c);
        } else if (type == 2) {
            // alternating starting with random
            char c = rnd.next(0, 1) ? 'B' : 'W';
            for (int j = 0; j < len; j++) {
                s.push_back(c);
                c = (c == 'B' ? 'W' : 'B');
            }
        } else {
            // block pattern: blocks of size 1-3, alternating
            char c = rnd.next(0, 1) ? 'B' : 'W';
            int pos = 0;
            while (pos < len) {
                int blk = rnd.next(1, 3);
                for (int j = 0; j < blk && pos < len; j++, pos++)
                    s.push_back(c);
                c = (c == 'B' ? 'W' : 'B');
            }
        }
        println(s);
    }
    return 0;
}
