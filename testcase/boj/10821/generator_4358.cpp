#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of integers
    double p = rnd.next();
    int n;
    if (p < 0.1) n = 1;
    else if (p < 0.3) n = rnd.next(2, 3);
    else if (p < 0.6) n = rnd.next(4, 6);
    else if (p < 0.9) n = rnd.next(7, 10);
    else n = rnd.next(1, 10);

    vector<int> Ts = {-2, -1, 0, 1, 2};
    string S;
    for (int i = 0; i < n; i++) {
        // Weighted digit length in [1..9]
        int t = rnd.any(Ts);
        int len = rnd.wnext(9, t) + 1;
        // First digit 1-9 (no leading zero)
        S.push_back(char('1' + rnd.next(0, 8)));
        // Remaining digits 0-9
        for (int j = 1; j < len; j++) {
            S.push_back(char('0' + rnd.next(0, 9)));
        }
        if (i + 1 < n) S.push_back(',');
    }

    println(S);
    return 0;
}
