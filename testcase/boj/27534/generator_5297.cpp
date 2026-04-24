#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int type = rnd.next(0, 3);
        int n;
        string s;
        if (type == 0) {
            // All zeros or all ones (impossible case)
            n = rnd.next(1, 20);
            char c = rnd.any(string("01"));
            s = string(n, c);
        } else if (type == 1) {
            // Already good string, cost = 0
            int m = rnd.next(1, 10);
            n = 2 * m;
            s = string(m, '0') + string(m, '1');
        } else if (type == 2) {
            // One change away from good
            int m = rnd.next(1, 9);
            n = 2 * m;
            s = string(m, '0') + string(m, '1');
            int p = rnd.next(1, n);
            s[p-1] = (s[p-1] == '0' ? '1' : '0');
        } else {
            // Random binary string (diverse cases)
            n = rnd.next(1, 20);
            s.clear();
            for (int i = 0; i < n; i++)
                s.push_back(rnd.any(string("01")));
        }
        println(n);
        printf("%s\n", s.c_str());
    }
    return 0;
}
