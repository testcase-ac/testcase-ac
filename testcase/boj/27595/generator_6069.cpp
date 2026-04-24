#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = rnd.next(1, 10);
    int len = 2 * n - 1;
    string s(len, '?');
    // Choose a generation strategy
    int op_max = (len >= 2 ? 4 : 3);
    int op = rnd.next(0, op_max);
    string letters = "RW";
    switch (op) {
        // all same
        case 0: {
            char c = rnd.any(letters);
            for (int i = 0; i < len; i++) s[i] = c;
            break;
        }
        // alternating pattern
        case 1: {
            char start = rnd.any(letters);
            char other = (start == 'R' ? 'W' : 'R');
            for (int i = 0; i < len; i++) {
                s[i] = (i % 2 == 0 ? start : other);
            }
            break;
        }
        // random toss with probability p
        case 2: {
            vector<double> ps = {0.1, 0.3, 0.5, 0.7, 0.9};
            double p = rnd.any(ps);
            for (int i = 0; i < len; i++) {
                s[i] = (rnd.next() < p ? 'W' : 'R');
            }
            break;
        }
        // block-wise alternating
        case 3: {
            int b = rnd.next(1, min(len, 5));
            vector<int> blocks(b, 1);
            int rem = len - b;
            for (int i = 0; i < b; i++) {
                int add = (i == b - 1 ? rem : rnd.next(0, rem));
                blocks[i] += add;
                rem -= add;
            }
            char c = rnd.any(letters);
            int pos = 0;
            for (int bl : blocks) {
                for (int k = 0; k < bl; k++) {
                    s[pos++] = c;
                }
                c = (c == 'R' ? 'W' : 'R');
            }
            break;
        }
        // prefix heavy then random
        case 4: {
            int k = rnd.next(1, len - 1);
            char c = rnd.any(letters);
            for (int i = 0; i < k; i++) s[i] = c;
            for (int i = k; i < len; i++) s[i] = rnd.any(letters);
            break;
        }
    }
    // Output
    println(n);
    println(s);
    return 0;
}
