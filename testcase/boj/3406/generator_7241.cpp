#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 6);
        string s;
        if (type == 0) {
            // Single bit
            s = string(1, char('0' + rnd.next(0, 1)));
        } else if (type == 1) {
            // All length-2 patterns
            vector<string> v = {"00", "01", "10", "11"};
            s = rnd.any(v);
        } else if (type == 2) {
            // Random bits, length 3–15
            int n = rnd.next(3, 15);
            s.resize(n);
            for (int j = 0; j < n; j++)
                s[j] = char('0' + rnd.next(0, 1));
        } else if (type == 3) {
            // Alternating pattern, length 3–20
            int n = rnd.next(3, 20);
            char first = char('0' + rnd.next(0, 1));
            s.resize(n);
            for (int j = 0; j < n; j++)
                s[j] = (j % 2 == 0 ? first : (first == '0' ? '1' : '0'));
        } else if (type == 4) {
            // Single 1 in zeros, length 3–20
            int n = rnd.next(3, 20);
            int k = rnd.next(0, n - 1);
            s.assign(n, '0');
            s[k] = '1';
        } else if (type == 5) {
            // Block of ones, length 5–25
            int n = rnd.next(5, 25);
            int b = rnd.next(1, n);
            int p = rnd.next(0, n - b);
            s.assign(n, '0');
            for (int j = p; j < p + b; j++)
                s[j] = '1';
        } else {
            // All zeros or all ones, length 3–15
            int n = rnd.next(3, 15);
            char c = char('0' + rnd.next(0, 1));
            s.assign(n, c);
        }
        println(s);
    }
    return 0;
}
