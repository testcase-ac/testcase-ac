#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int t = rnd.next(5, 12);
    println(t);
    int total = 0;
    for (int tc = 0; tc < t; tc++) {
        // Choose length n, keep sum under 2000
        int rem = 2000 - total;
        int maxn = min(rem, 30);
        int n = rnd.next(1, maxn);
        total += n;

        // Pick a pattern type
        int tp = rnd.next(0, 5);
        string s;
        s.reserve(n);

        if (tp == 0) {
            // Pure random
            for (int i = 0; i < n; i++) {
                s.push_back(rnd.next(0,1) ? 'A' : 'B');
            }
        } else if (tp == 1) {
            // No "ABB": avoid placing B when last two are 'A','B'
            for (int i = 0; i < n; i++) {
                if (i >= 2 && s[i-2]=='A' && s[i-1]=='B') {
                    s.push_back('A');
                } else {
                    s.push_back(rnd.next(0,1) ? 'A' : 'B');
                }
            }
        } else if (tp == 2 && n >= 3) {
            // Many "ABB"
            int maxk = n / 3;
            int k = rnd.next(1, maxk);
            for (int i = 0; i < k; i++) {
                s += "ABB";
            }
            while ((int)s.size() < n) {
                s.push_back(rnd.next(0,1) ? 'A' : 'B');
            }
        } else if (tp == 3 && n >= 2) {
            // Overlapping ABB: "A" then all Bs
            s.push_back('A');
            for (int i = 1; i < n; i++) s.push_back('B');
        } else if (tp == 4) {
            // Monotonic
            char c = rnd.any(string("AB"));
            for (int i = 0; i < n; i++) s.push_back(c);
        } else if (tp == 5) {
            // Alternating AB
            for (int i = 0; i < n; i++) {
                s.push_back((i % 2 == 0) ? 'A' : 'B');
            }
        } else {
            // Fallback to random
            for (int i = 0; i < n; i++) {
                s.push_back(rnd.next(0,1) ? 'A' : 'B');
            }
        }

        println(n);
        printf("%s\n", s.c_str());
    }

    return 0;
}
