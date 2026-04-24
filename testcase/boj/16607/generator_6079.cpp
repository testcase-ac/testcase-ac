#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose length with some edge weights
    int coin = rnd.next(0, 9);
    int len;
    if (coin == 0) len = 1;
    else if (coin == 1) len = 20;
    else len = rnd.next(2, 19);

    // Mode: 0-1 horizontal only (alternating L/R), 2-3 vertical only (U/D), else mixed
    int mode = rnd.next(0, 9);
    const string LR = "LR";
    const string UD = "UD";
    const string ALL = "LRUD";
    string s;
    s.reserve(len);

    if (mode < 2) {
        // Horizontal only: alternate L/R
        char c = rnd.any(LR);
        s.push_back(c);
        for (int i = 1; i < len; i++) {
            char other = (s.back() == 'L') ? 'R' : 'L';
            s.push_back(other);
        }
    } else if (mode < 4) {
        // Vertical only: alternate U/D
        char c = rnd.any(UD);
        s.push_back(c);
        for (int i = 1; i < len; i++) {
            char other = (s.back() == 'U') ? 'D' : 'U';
            s.push_back(other);
        }
    } else {
        // Mixed: pick any direction, avoid repeats
        s.push_back(rnd.any(ALL));
        for (int i = 1; i < len; i++) {
            char c;
            do {
                c = rnd.any(ALL);
            } while (c == s.back());
            s.push_back(c);
        }
    }

    // Output the move sequence
    println(s);
    return 0;
}
