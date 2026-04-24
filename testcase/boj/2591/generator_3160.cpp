#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int mode = rnd.next(0, 2);
    string s;
    if (mode == 0) {
        // Build string by concatenating random cards (1 to 34)
        int k = rnd.next(1, 8);
        for (int i = 0; i < k; i++) {
            int x = rnd.next(1, 34);
            s += to_string(x);
        }
    } else if (mode == 1) {
        // Pure random digit string (no leading zero)
        int n = rnd.next(1, 12);
        s.resize(n);
        s[0] = char('1' + rnd.next(0, 8));  // '1' to '9'
        for (int i = 1; i < n; i++) {
            s[i] = char('0' + rnd.next(0, 9));
        }
    } else {
        // Ambiguous pattern: repeated digit for many splits
        int t = rnd.next(3, 8);
        char d = rnd.any(string("123"));
        s = string(t, d);
    }
    println(s);
    return 0;
}
